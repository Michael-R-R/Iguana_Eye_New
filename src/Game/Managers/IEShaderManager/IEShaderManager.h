#pragma once

#include <QDataStream>

#include "IEManager.h"
#include "IEShader.h"
#include "IEGlslImporter.h"

class GameStartEvent;

class IEShaderManager : public IEManager<IEShader>
{
    Q_OBJECT

public:
    IEShaderManager();
    ~IEShaderManager();

    void startup(const GameStartEvent& event) override;
    void shutdown() override;

    bool add(const unsigned long long key, std::unique_ptr<IEShader> value) override;
    bool remove(const unsigned long long key) override;
    bool changeKey(const unsigned long long oldKey, const unsigned long long newKey) override;

private:
    void buildAllShaders();

signals:
    void added(const unsigned long long key, const QString& path);
    void removed(const unsigned long long key);
    void keyChanged(const unsigned long long oldKey, const unsigned long long newKey);

public:
    friend QDataStream& operator<<(QDataStream& out, const IEShaderManager& manager)
    {
        const auto* resources = manager.getResourceContainer().getResources();

        out << (int)resources->size();

        for(auto& item : *resources)
        {
            out << item.second->getFilePath()
                << item.second->getId()
                << item.second->getType();
        }

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEShaderManager& manager)
    {
        int size = 0;
        in >> size;

        QString path = "";
        unsigned long long id = 0;
        IEResource::Type type;
        std::unique_ptr<IEShader> shader = nullptr;

        for(int i = 0; i < size; i++)
        {
            in >> path >> id >> type;

            if(type == IEResource::Type::Editor)
                continue;

            shader = std::make_unique<IEShader>(path, id);
            if(!IEGlslImporter::importGlsl(path, *shader))
                continue;

            manager.add(id, std::move(shader));
        }

        return in;
    }
};
