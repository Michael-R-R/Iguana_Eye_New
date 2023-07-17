#include "IERenderableManager.h"
#include "ApplicationWindow.h"
#include "IERenderable.h"
#include "IEShader.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableFactory.h"

IERenderableManager::IERenderableManager(QObject* parent) :
    IEResourceManager(parent)
{

}

IERenderableManager::~IERenderableManager()
{

}

QDataStream& IERenderableManager::serialize(QDataStream& out, const IESerializable& obj) const
{
    IEResourceManager::serialize(out, obj);

    const IERenderableManager& manager = static_cast<const IERenderableManager&>(obj);

    out << (int)manager.resources.size();

    foreach (auto* i, manager.resources)
    {
        auto* r = static_cast<IERenderable*>(i);

        out << r->getType();
        out << *r;
    }

    return out;
}

QDataStream& IERenderableManager::deserialize(QDataStream& in, IESerializable& obj)
{
    IEResourceManager::deserialize(in, obj);

    IERenderableManager& manager = static_cast<IERenderableManager&>(obj);

    int count = 0;
    in >> count;

    auto* game = ApplicationWindow::instance().getGame();
    auto* scene = game->getSystem<IEScene>();
    auto* maManager = scene->getSystem<IEMaterialManager>();
    auto* sManager = scene->getSystem<IEShaderManager>();

    IERenderableType type = IERenderableType::Unknown;
    for(int i = 0; i < count; i++)
    {
        in >> type;

        auto* renderable = IERenderableFactory::make(type, &manager);
        if(!renderable)
            continue;

        in >> *renderable;

        if(!maManager->doesExist(renderable->getMaterialID()) ||
           !sManager->doesExist(renderable->getShaderID()))
        {
            delete renderable;
            continue;
        }

        auto* shader = sManager->value<IEShader>(renderable->getShaderID());
        const int nodeCount = renderable->getNodes().size();
        for(int i = 0; i < nodeCount; i++)
        {
            if(!renderable->build(i, *shader))
            {
                delete renderable;
                continue;
            }
        }

        if(!manager.add(renderable->getID(), renderable))
            delete renderable;
    }

    return in;
}
