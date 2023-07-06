#pragma once

#include "IEBaseRigidbody.h"

class IESphereRigidbody : public IEBaseRigidbody
{
    float radius;

public:
    IESphereRigidbody(QObject* parent = nullptr);
    IESphereRigidbody(RigidbodyType type,
                      const int id,
                      const float r,
                      const float d = 0.0f,
                      const float st = 0.0f,
                      QObject* parent = nullptr);
    ~IESphereRigidbody();

    void create(const physx::PxTransform& t) override;

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};

