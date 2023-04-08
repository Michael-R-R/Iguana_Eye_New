#pragma once

#include "IEResourceManager.h"
#include "IEMaterial.h"

class GameStartEvent;

class IEMaterialManager: public IEResourceManager<IEMaterial>
{
    Q_OBJECT

public:
    IEMaterialManager();
    ~IEMaterialManager();

    bool add(const unsigned long long key, QSharedPointer<IEMaterial> value) override;
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
