#pragma once

#include <QDataStream>

#include "IEResourceManager.h"
#include "IEShader.h"
#include "IEGlslImporter.h"

class GameStartEvent;

class IEShaderManager : public IEResourceManager<IEShader>
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
        out << (int)manager.resources.size();

        for(auto& i : manager.resources)
        {
            auto& shader = *i.second;

            out << shader.getType();

            if(shader.getType() != IEResource::Type::Game)
                continue;

            out << shader.getFilePath() << shader.getId();
        }

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEShaderManager& manager)
    {
        int size = 0;
        in >> size;

        IEResource::Type type;
        QString path = "";
        unsigned long long id = 0;

        for(int i = 0; i < size; i++)
        {
            in >> type;

            if(type != IEResource::Type::Game)
                continue;

            in >> path >> id;

            auto shader = std::make_unique<IEShader>(path, id);
            if(!IEGlslImporter::importGlsl(path, *shader))
                continue;

            manager.add(id, std::move(shader));
        }

        return in;
    }
};
