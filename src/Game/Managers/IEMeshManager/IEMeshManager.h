#pragma once

#include "IEResourceManager.h"
#include "IEMesh.h"

class GameStartEvent;

class IEMeshManager : public IEResourceManager<IEMesh>
{
    Q_OBJECT

public:
    IEMeshManager();
    ~IEMeshManager();

    bool add(const unsigned long long key, std::unique_ptr<IEMesh> value) override;
    bool remove(const unsigned long long key) override;
    bool changeKey(const unsigned long long oldKey, const unsigned long long newKey) override;

signals:
    void added(const unsigned long long key, const QString& path);
    void removed(const unsigned long long key);
    void keyChanged(const unsigned long long oldKey, const unsigned long long newKey);

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
