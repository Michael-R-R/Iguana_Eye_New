#pragma once

#include <QDataStream>

#include "IEECSResourceSystem.h"

class IEShader;
class IEShaderManager;

class IEECSShaderSystem : public IEECSResourceSystem
{
    IEShaderManager* shaderManager;

public:
    IEECSShaderSystem(QObject* parent = nullptr);
    ~IEECSShaderSystem();

    void startUp(const IEGame& game) override;
    void shutdown(const IEGame& game) override;

    IEShader* getAttachedResource(const int index);

    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;
};

