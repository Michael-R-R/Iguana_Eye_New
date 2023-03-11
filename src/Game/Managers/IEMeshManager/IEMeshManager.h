#pragma once

#include <QDataStream>

#include "IEManager.h"
#include "IEMesh.h"
#include "IEObjImporter.h"

class GameStartEvent;

class IEMeshManager : public IEManager<IEMesh>
{
    Q_OBJECT

public:
    IEMeshManager();
    ~IEMeshManager();

    void startup(const GameStartEvent& event) override;
    void shutdown() override;

    bool add(const unsigned long long key, IEMesh* value) override;
    bool remove(const unsigned long long key) override;
    bool changeKey(const unsigned long long oldKey, const unsigned long long newKey) override;

signals:
    void added(const unsigned long long key, const QString& value);
    void removed(const unsigned long long key);
    void keyChanged(const unsigned long long oldKey, const unsigned long long newKey);

public:
    friend QDataStream& operator<<(QDataStream& out, const IEMeshManager& manager)
    {
        auto& resources = manager.getResourceContainer()->getResources();

        out << (int)resources.size();

        for(auto item : resources)
        {
            out << item->getFilePath() << item->getId() << item->getType();
        }

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEMeshManager& manager)
    {
        int size = 0;
        in >> size;

        QString path = "";
        unsigned long long id = 0;
        IEResource::Type type;
        IEMesh* mesh = nullptr;

        for(int i = 0; i < size; i++)
        {
            in >> path >> id >> type;

            if(type == IEResource::Type::Editor)
                continue;

            mesh = new IEMesh(path, id);
            if(!IEObjImporter::importMesh(path, mesh))
            {
                delete mesh;
                continue;
            }

            manager.add(mesh->getId(), mesh);
        }

        return in;
    }
};
