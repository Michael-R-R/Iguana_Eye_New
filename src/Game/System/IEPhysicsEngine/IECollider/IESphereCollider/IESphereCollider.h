#pragma once

#include "IEBaseCollider.h"

class IESphereCollider : public IEBaseCollider
{
    float radius;

public:
    IESphereCollider(QObject* parent = nullptr);
    IESphereCollider(const int id, const float r, QObject* parent = nullptr);
    IESphereCollider(const IESphereCollider&) = delete;
    ~IESphereCollider();

    void create(const physx::PxTransform& t) override;

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};

