#pragma once

#include "IEResourceManager.h"

class IERenderableManager : public IEResourceManager
{

public:
    IERenderableManager(QObject* parent = nullptr);
    ~IERenderableManager();

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
