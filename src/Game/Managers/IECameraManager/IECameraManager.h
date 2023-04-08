#pragma once

#include "IEResourceManager.h"
#include "IECamera.h"

class IECameraManager : public IEResourceManager<IECamera>
{
    Q_OBJECT

public:
    IECameraManager();
    ~IECameraManager();

    bool add(const unsigned long long key, QSharedPointer<IECamera> value) override;
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

