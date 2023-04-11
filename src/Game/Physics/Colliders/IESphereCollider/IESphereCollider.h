#pragma once

#include "IEBaseCollider.h"

class IESphereCollider : public IEBaseCollider
{
    float radius;

public:
    IESphereCollider();
    IESphereCollider(const int id, const float r);
    IESphereCollider(const IESphereCollider&) = delete;
    ~IESphereCollider();

    void create(const physx::PxTransform& t) override;

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

