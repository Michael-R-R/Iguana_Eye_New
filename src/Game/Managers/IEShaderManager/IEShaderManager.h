#pragma once

#include <QDataStream>

#include "IEManager.h"
#include "IESerialize.h"
#include "IEShader.h"

class GameStartEvent;

class IEShaderManager : public IEManager<IEShader>
{
    Q_OBJECT

public:
    IEShaderManager(QObject* parent = nullptr);
    ~IEShaderManager();

    void startup(const GameStartEvent& event) override;
    void shutdown() override;

    bool add(const unsigned long long key, IEShader* value) override;
    bool remove(const unsigned long long key) override;
    bool changeKey(const unsigned long long oldKey, const unsigned long long newKey) override;

private:
    void buildAllShaders();

signals:
    void added(const unsigned long long key);
    void removed(const unsigned long long key);
    void keyChanged(const unsigned long long oldKey, const unsigned long long newKey);

public:
    friend QDataStream& operator<<(QDataStream& out, const IEShaderManager& manager)
    {
        auto& resources = manager.getResourceContainer()->getResources();

        out << (int)resources.size();

        for(auto item : resources)
        {
            out << item->getFilePath();
        }

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEShaderManager& manager)
    {
        int size = 0;
        in >> size;

        QString filePath = "";
        IEShader* shader = nullptr;

        for(int i = 0; i < size; i++)
        {
            in >> filePath;

            shader = new IEShader();
            if(!IESerialize::read<IEShader>(filePath, shader))
            {
                delete shader;
                continue;
            }

            manager.add(shader->getId(), shader);
        }

        return in;
    }
};
