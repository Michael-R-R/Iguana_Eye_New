#include "IERenderableManager.h"
#include "IEScene.h"
#include "IEShaderManager.h"

IERenderableManager::IERenderableManager() :
    IEResourceManager()
{

}

IERenderableManager::~IERenderableManager()
{

}

bool IERenderableManager::add(const unsigned long long key, QSharedPointer<IERenderable> value)
{
    if(!IEResourceManager::add(key, value))
        return false;

    emit added(key, value->getFilePath());

    return true;
}

bool IERenderableManager::remove(const unsigned long long key)
{
    if(!IEResourceManager::remove(key))
        return false;

    emit removed(key);

    return true;
}

bool IERenderableManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!IEResourceManager::changeKey(oldKey, newKey))
        return false;

    emit keyChanged(oldKey, newKey);

    return true;
}

bool IERenderableManager::doesExist(const unsigned long long meshId,
                                    const unsigned long long materialId,
                                    const unsigned long long shaderId)
{
    for(auto& i : resources)
    {
        if(i->equals(meshId, materialId, shaderId))
            return true;
    }

    return false;
}

void IERenderableManager::buildAll()
{
    auto& shaderManager = IEScene::instance().getShaderManager();

    for(auto& i : resources)
    {
        auto shader = shaderManager.value(i->getShaderId());
        if(!shader)
            continue;

        i->build(*shader);
    }
}

QDataStream& IERenderableManager::serialize(QDataStream& out, const Serializable& obj) const
{
    return IEResourceManager::serialize(out, obj);
}

QDataStream& IERenderableManager::deserialize(QDataStream& in, Serializable& obj)
{
    IEResourceManager::deserialize(in, obj);

    IERenderableManager& manager = static_cast<IERenderableManager&>(obj);
    manager.buildAll();

    return in;
}
