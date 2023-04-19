#pragma once

#include "IEBaseCollider.h"

class IEBoxCollider : public IEBaseCollider
{
    float extentX, extentY, extentZ;

public:
    IEBoxCollider(QObject* parent = nullptr);
    IEBoxCollider(const int id,
                  const float x, const float y, const float z,
                  QObject* parent = nullptr);
    IEBoxCollider(const IEBoxCollider&) = delete;
    ~IEBoxCollider();

    void create(const physx::PxTransform& t) override;

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

