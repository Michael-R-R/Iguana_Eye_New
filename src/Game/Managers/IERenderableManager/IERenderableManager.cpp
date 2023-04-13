#include "IERenderableManager.h"
#include "ApplicationWindow.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
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

void IERenderableManager::importAll()
{
    QVector<unsigned long long> markedForRemove;

    auto* game = ApplicationWindow::instance().getGame();
    auto& scene = game->getScene();
    auto& meshManager = scene.getMeshManager();
    auto& materialManager = scene.getMaterialManager();
    auto& shaderManager = scene.getShaderManager();

    for(auto& i : resources)
    {
        if(!meshManager.doesExist(i->getMeshId()))
        {
            markedForRemove.push_back(i->getId());
            continue;
        }

        if(!materialManager.doesExist(i->getMaterialId()))
        {
            markedForRemove.push_back(i->getId());
            continue;
        }

        if(!shaderManager.doesExist(i->getShaderId()))
        {
            markedForRemove.push_back(i->getId());
            continue;
        }

        auto shader = shaderManager.value(i->getShaderId());
        if(!shader)
            continue;

        i->build(*shader);
    }

    for(auto& i : markedForRemove)
    {
        IERenderableManager::remove(i);
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
    manager.importAll();

    return in;
}
