#include "IEECSShaderSystem.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEShaderManager.h"
#include "IEShader.h"

IEECSShaderSystem::IEECSShaderSystem(QObject* parent) :
    IEECSResourceSystem(typeid(IEECSShaderSystem).hash_code(), parent),
    shaderManager(nullptr)
{
    IEECSShaderSystem::attach(IEEntity(-1));
}

IEECSShaderSystem::~IEECSShaderSystem()
{

}

void IEECSShaderSystem::startUp(const IEGame& game)
{
    shaderManager = game.getSystem<IEScene>()->getManager<IEShaderManager>();
}

void IEECSShaderSystem::shutdown(const IEGame&)
{
    shaderManager = nullptr;
}

IEShader* IEECSShaderSystem::getAttachedResource(const int index)
{
    return IEECSResourceSystem::getAttachedResource<IEShader>(index, shaderManager);
}

QDataStream& IEECSShaderSystem::serialize(QDataStream& out, const IESerializable& obj) const
{
    return IEECSResourceSystem::serialize(out, obj);
}

QDataStream& IEECSShaderSystem::deserialize(QDataStream& in, IESerializable& obj)
{
    return IEECSResourceSystem::deserialize(in, obj);
}
