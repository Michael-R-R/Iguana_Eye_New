#pragma once

#include <QDataStream>

#include "IEResourceManager.h"
#include "IEMesh.h"
#include "IEObjImporter.h"

class GameStartEvent;

class IEMeshManager : public IEResourceManager<IEMesh>
{
    Q_OBJECT

public:
    IEMeshManager();
    ~IEMeshManager();

    void startup(const GameStartEvent& event) override;
    void shutdown() override;

    bool add(const unsigned long long key, std::unique_ptr<IEMesh> value) override;
    bool remove(const unsigned long long key) override;
    bool changeKey(const unsigned long long oldKey, const unsigned long long newKey) override;

signals:
    void added(const unsigned long long key, const QString& path);
    void removed(const unsigned long long key);
    void keyChanged(const unsigned long long oldKey, const unsigned long long newKey);

public:
    friend QDataStream& operator<<(QDataStream& out, const IEMeshManager& manager)
    {
        out << (int)manager.resources.size();

        for(auto& i : manager.resources)
        {
            auto& mesh = *i.second;

            out << mesh.getType();

            if(mesh.getType() != IEResource::Type::Game)
                continue;

            out << mesh.getFilePath() << mesh.getId();
        }

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEMeshManager& manager)
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

            auto mesh = std::make_unique<IEMesh>(path, id);
            if(!IEObjImporter::importMesh(path, *mesh))
                continue;

            manager.add(id, std::move(mesh));
        }

        return in;
    }
};
