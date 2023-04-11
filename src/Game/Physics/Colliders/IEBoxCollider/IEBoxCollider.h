#pragma once

#include "IEBaseCollider.h"

class IEBoxCollider : public IEBaseCollider
{
    float extentX, extentY, extentZ;

public:
    IEBoxCollider();
    IEBoxCollider(const int id,
                  const float x, const float y, const float z);
    IEBoxCollider(const IEBoxCollider&) = delete;
    ~IEBoxCollider();

    void create(const physx::PxTransform& t) override;

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

