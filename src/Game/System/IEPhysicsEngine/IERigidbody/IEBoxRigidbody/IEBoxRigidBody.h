#pragma once

#include "IEBaseRigidbody.h"

class IEBoxRigidbody : public IEBaseRigidbody
{
    float extentX, extentY, extentZ;

public:
    IEBoxRigidbody(QObject* parent = nullptr);
    IEBoxRigidbody(RigidbodyType type,
                   const int id,
                   const float x, const float y, const float z,
                   const float d = 0.0f,
                   const float st = 0.0f,
                   QObject* parent = nullptr);
    IEBoxRigidbody(const IEBoxRigidbody&) = delete;
    ~IEBoxRigidbody();

    void create(const physx::PxTransform& t) override;

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};

