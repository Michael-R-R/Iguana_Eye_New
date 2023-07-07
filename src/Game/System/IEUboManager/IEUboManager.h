#pragma once

#include "IESystem.h"
#include "IEUniformBufferObject.h"
#include "GLViewProjectionStruct.h"

class IEShader;

class IEUboManager : public IESystem
{
    IEUniformBufferObject<GLViewProjectionStruct>* vpBuffer;

public:
    IEUboManager(QObject* parent = nullptr);
    virtual ~IEUboManager();

    void startup(IEGame& game) override;
    void shutdown(IEGame& game) override;

    void cleanup();

    IEUniformBufferObject<GLViewProjectionStruct>* getVPBuffer() { return vpBuffer; }

private slots:
    void linkProgramToBlock(const uint64_t key, const QString& path);

public:
    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;

};

