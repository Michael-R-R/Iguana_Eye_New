#include "IEUboManager.h"
#include "IEUniformBufferObject.h"
#include "GLSViewProjection.h"
#include "GLSCamera.h"
#include "ApplicationWindow.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEShaderManager.h"
#include "IEShader.h"

IEUboManager::IEUboManager(QObject* parent) :
    IESystem(parent),
    vpBuffer(nullptr), cameraBuffer(nullptr)
{

}

IEUboManager::~IEUboManager()
{

}

void IEUboManager::startup(IEGame& game)
{
    auto* scene = game.getSystem<IEScene>();
    auto* sManager = scene->getSystem<IEShaderManager>();
    connect(sManager, &IEShaderManager::added, this, &IEUboManager::linkProgramToBlock);

    vpBuffer = new IEUniformBufferObject<GLSViewProjection>("ubViewProjection", 0, 1, this);
    cameraBuffer = new IEUniformBufferObject<GLSCamera>("ubCamera", 1, 1, this);

    vpBuffer->build();
    cameraBuffer->build();
}

void IEUboManager::shutdown(IEGame& game)
{
    auto* scene = game.getSystem<IEScene>();
    auto* sManager = scene->getSystem<IEShaderManager>();
    disconnect(sManager, &IEShaderManager::added, this, &IEUboManager::linkProgramToBlock);

    cleanup();
}

void IEUboManager::linkShaderToBlock(IEShader& shader)
{
    linkAllBlocks(shader);
}

void IEUboManager::cleanup()
{
    delete vpBuffer;
    delete cameraBuffer;

    vpBuffer = nullptr;
    cameraBuffer = nullptr;
}

void IEUboManager::linkProgramToBlock(const uint64_t key, const QString&)
{
    auto* game = ApplicationWindow::instance().getGame();
    auto* scene = game->getSystem<IEScene>();
    auto* sManager = scene->getSystem<IEShaderManager>();
    auto* shader = sManager->value<IEShader>(key);
    if(!shader)
        return;

    linkAllBlocks(*shader);
}

void IEUboManager::linkAllBlocks(IEShader& shader)
{
    if(!shader.isLinked())
        return;

    const int program = shader.programId();

    vpBuffer->linkBlock(program);
    cameraBuffer->linkBlock(program);
}

QDataStream& IEUboManager::serialize(QDataStream& out, const IESerializable& obj) const
{
    IESystem::serialize(out, obj);

    const auto& manager = static_cast<const IEUboManager&>(obj);

    out << *manager.vpBuffer
        << *manager.cameraBuffer;

    return out;
}

QDataStream& IEUboManager::deserialize(QDataStream& in, IESerializable& obj)
{
    IESystem::deserialize(in, obj);

    auto& manager = static_cast<IEUboManager&>(obj);

    in >> *manager.vpBuffer
       >> *manager.cameraBuffer;

    return in;
}
