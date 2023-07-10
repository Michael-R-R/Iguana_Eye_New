#pragma once

#include "IESystem.h"

class IEShader;

template<class T>
class IEUniformBufferObject;
struct GLSViewProjection;
struct GLSCamera;

class IEUboManager : public IESystem
{
    IEUniformBufferObject<GLSViewProjection>* vpBuffer;
    IEUniformBufferObject<GLSCamera>* cameraBuffer;

public:
    IEUboManager(QObject* parent = nullptr);
    virtual ~IEUboManager();

    void startup(IEGame& game) override;
    void shutdown(IEGame& game) override;

    void linkShaderToBlock(IEShader& shader);
    void cleanup();

    IEUniformBufferObject<GLSViewProjection>* getVPBuffer() { return vpBuffer; }
    IEUniformBufferObject<GLSCamera>* getCameraBuffer() { return cameraBuffer; }

private slots:
    void linkProgramToBlock(const uint64_t key, const QString& path);

private:
    void linkAllBlocks(IEShader& shader);

public:
    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;

};

