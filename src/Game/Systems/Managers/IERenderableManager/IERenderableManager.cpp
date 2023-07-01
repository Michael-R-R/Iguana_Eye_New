#include "IERenderableManager.h"
#include "ApplicationWindow.h"
#include "IERenderable.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IEShader.h"
#include "IESerialize.h"

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

    for(auto* i : qAsConst(manager.resources))
    {
        out << i->getName();

        IESerialize::write<IERenderable>(i->getName(), static_cast<IERenderable*>(i));
    }

    return out;
}

QDataStream& IERenderableManager::deserialize(QDataStream& in, Serializable& obj)
{
    IERenderableManager& manager = static_cast<IERenderableManager&>(obj);

    int size = 0;
    in >> size;

    auto* game = ApplicationWindow::instance().getGame();
    auto* scene = game->getSystem<IEScene>();
    auto* materialManager = scene->getManager<IEMaterialManager>();
    auto* shaderManager = scene->getManager<IEShaderManager>();

    for(int i = 0; i < size; i++)
    {
        // TODO implement
    }

    return in;
}
