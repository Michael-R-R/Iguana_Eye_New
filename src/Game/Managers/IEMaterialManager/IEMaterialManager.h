#pragma once

#include <QDataStream>

#include "IEManager.h"
#include "IESerialize.h"
#include "IEMaterial.h"

class GameStartEvent;

class IEMaterialManager: public IEManager<IEMaterial>
{
    Q_OBJECT

public:
    IEMaterialManager(QObject* parent = nullptr);
    ~IEMaterialManager();

    void startup(const GameStartEvent& event) override;
    void shutdown() override;

    bool add(const unsigned long long key, IEMaterial* value) override;
    bool remove(const unsigned long long key) override;
    bool changeKey(const unsigned long long oldKey, const unsigned long long newKey) override;

signals:
    void added(const unsigned long long key, const QString& value);
    void removed(const unsigned long long key);
    void keyChanged(const unsigned long long oldKey, const unsigned long long newKey);

public:
    friend QDataStream& operator<<(QDataStream& out, const IEMaterialManager& manager)
    {
        auto& resources = manager.getResourceContainer()->getResources();

        out << (int)resources.size();

        for(auto item : resources)
        {
            out << item->getFilePath() << item->getType();
        }

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEMaterialManager& manager)
    {
        int size = 0;
        in >> size;

        QString filePath = "";
        IEResource::Type type;
        IEMaterial* material = nullptr;

        for(int i = 0; i < size; i++)
        {
            in >> filePath >> type;

            if(type == IEResource::Type::Editor)
                continue;

            material = new IEMaterial();
            if(!IESerialize::read<IEMaterial>(filePath, material))
            {
                delete material;
                continue;
            }

            manager.add(material->getId(), material);
        }

        return in;
    }
};
