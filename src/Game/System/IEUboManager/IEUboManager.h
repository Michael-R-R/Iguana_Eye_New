#pragma once

#include "IESystem.h"
#include "IEUniformBufferObject.h"
#include "glm/glm.hpp"

class IEShader;

class IEUboManager : public IESystem
{
    IEUniformBufferObject<glm::mat4>* vpBuffer;

public:
    IEUboManager(QObject* parent = nullptr);
    virtual ~IEUboManager();

    void startup(IEGame& game) override;
    void shutdown(IEGame& game) override;

    void linkShaderToBlock(IEShader& shader);
    void cleanup();

    IEUniformBufferObject<glm::mat4>* getVPBuffer() { return vpBuffer; }

private slots:
    void linkProgramToBlock(const uint64_t key, const QString& path);

private:
    void linkAllBlocks(IEShader& shader);

public:
    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;

};

