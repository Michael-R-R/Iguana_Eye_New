#pragma once

#include <QDataStream>

#include "IEManager.h"
#include "IEMesh.h"

class GameStartEvent;

class IEMeshManager : public IEManager<IEMesh>
{
    Q_OBJECT

public:
    IEMeshManager(QObject* parent = nullptr);
    ~IEMeshManager();

    void startup(const GameStartEvent& event) override;
    void shutdown() override;

    bool add(const unsigned long long key, IEMesh* value) override;
    bool remove(const unsigned long long key) override;
    bool changeKey(const unsigned long long oldKey, const unsigned long long newKey) override;

signals:
    void added(const unsigned long long key);
    void removed(const unsigned long long key);
    void keyChanged(const unsigned long long oldKey, const unsigned long long newKey);

public:
    friend QDataStream& operator<<(QDataStream& out, const IEMeshManager& manager)
    {


        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEMeshManager& manager)
    {


        return in;
    }
};
