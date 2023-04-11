#include "IEShaderManager.h"
#include "IEDefaultShader.h"
#include "IEFile.h"

IEShaderManager::IEShaderManager() :
    IEResourceManager()
{
    auto shader = QSharedPointer<IEDefaultShader>::create(IEFile::absolutePath("./resources/shaders/game/default.glsl"));
    shader->build();
    defaultId = shader->getId();
    IEShaderManager::add(defaultId, shader);
}

IEShaderManager::~IEShaderManager()
{

}

bool IEShaderManager::add(const unsigned long long key, QSharedPointer<IEShader> value)
{
    if(!IEResourceManager::add(key, value))
        return false;

    emit added(key, value->getFilePath());

    return true;
}

bool IEShaderManager::remove(const unsigned long long key)
{
    if(!IEResourceManager::remove(key))
        return false;

    emit removed(key);

    return true;
}

bool IEShaderManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!IEResourceManager::changeKey(oldKey, newKey))
        return false;

    emit keyChanged(oldKey, newKey);

    return true;
}

void IEShaderManager::buildAll()
{
    for(auto& i : resources)
    {
        i->build();
    }
}

QDataStream& IEShaderManager::serialize(QDataStream& out, const Serializable& obj) const
{
    return IEResourceManager::serialize(out, obj);
}

QDataStream& IEShaderManager::deserialize(QDataStream& in, Serializable& obj)
{
    IEResourceManager::deserialize(in, obj);

    auto& manager = static_cast<IEShaderManager&>(obj);
    manager.buildAll();

    return in;
}
