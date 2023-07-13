#include "IERenderableManager.h"
#include "ApplicationWindow.h"
#include "IERenderable.h"
#include "IEShader.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableFactory.h"
#include "IESerialize.h"

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

        out << r->getName() << r->getType();

        IESerialize::write<IERenderable>(r->getName(), r);
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
    auto* meManager = scene->getManager<IEMeshManager>();
    auto* maManager = scene->getManager<IEMaterialManager>();
    auto* sManager = scene->getManager<IEShaderManager>();

    QString path = "";
    IERenderableType type = IERenderableType::Unknown;
    for(int i = 0; i < count; i++)
    {
        in >> path >> type;

        auto* renderable = IERenderableFactory::make(type, &manager);
        if(!renderable)
            continue;

        if(!IESerialize::read<IERenderable>(path, renderable))
        {
            delete renderable;
            continue;
        }

        if(!meManager->doesExist(renderable->getMeshID()) ||
           !maManager->doesExist(renderable->getMaterialID()) ||
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
