#include "IERenderableManager.h"
#include "ApplicationWindow.h"
#include "IERenderable.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IEShader.h"

IERenderableManager::IERenderableManager(QObject* parent) :
    IEResourceManager(parent)
{

}

IERenderableManager::~IERenderableManager()
{

}

QDataStream& IERenderableManager::serialize(QDataStream& out, const Serializable& obj) const
{
    const IERenderableManager& manager = static_cast<const IERenderableManager&>(obj);

    out << (int)manager.resources.size();

    for(auto* i : manager.resources)
    {
        out << *static_cast<IERenderable*>(i);
    }

    return out;
}

QDataStream& IERenderableManager::deserialize(QDataStream& in, Serializable& obj)
{
    IERenderableManager& manager = static_cast<IERenderableManager&>(obj);
    manager.clear();

    int size = 0;
    in >> size;

    auto* game = ApplicationWindow::instance().getGame();
    auto* scene = game->getScene();
    auto* meshManager = scene->getMeshManager();
    auto* materialManager = scene->getMaterialManager();
    auto* shaderManager = scene->getShaderManager();

    IERenderable* renderable = nullptr;

    for(int i = 0; i < size; i++)
    {
        renderable = new IERenderable(&manager);

        in >> *renderable;

        if(!meshManager->doesExist(renderable->getMeshId()))
        {
            delete renderable;
            continue;
        }

        if(!materialManager->doesExist(renderable->getMaterialId()))
        {
            delete renderable;
            continue;
        }

        if(!shaderManager->doesExist(renderable->getShaderId()))
        {
            delete renderable;
            continue;
        }

        if(!manager.add(renderable->getId(), renderable))
            delete renderable;
        else
        {
            auto* shader = shaderManager->value<IEShader>(renderable->getShaderId());
            renderable->build(*shader);
        }
    }

    return in;
}
