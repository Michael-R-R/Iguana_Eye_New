#include "IEECS.h"
#include "GameStartEvent.h"
#include "IEEntityManager.h"
#include "IEECSSystem.h"
#include "IEECSNameSystem.h"
#include "IEECSHierarchySystem.h"
#include "IEECSInputSystem.h"
#include "IEECSScriptSystem.h"
#include "IEECSTransformSystem.h"
#include "IEECSCameraSystem.h"
#include "IEECSMeshSystem.h"
#include "IEECSMaterialSystem.h"
#include "IEECSShaderSystem.h"
#include "IEECSRenderableSystem.h"
#include "ECSOnUpdateEvent.h"

IEECS::IEECS() :
    IEObject(),
    onUpdateEvent(nullptr),
    entityManager(new IEEntityManager()),
    systems()
{
    initSystems();
}

IEECS::~IEECS()
{
    delete onUpdateEvent;
    delete entityManager;
    clearSystems();
}

void IEECS::startup(const GameStartEvent& event)
{
    for(auto* system : qAsConst(systems))
    {
        system->startup(event);
    }

    onUpdateEvent = new ECSOnUpdateEvent(this);

    // TODO test
    auto* scriptSystem = this->getComponent<IEECSScriptSystem>(IEComponentType::Script);
    IEEntity entity = this->create();
    int index = this->attachComponent(entity, IEComponentType::Script);
    scriptSystem->addScript(index, new IEEntityScript("./resources/scripts/test/test1.lua", 1));
    scriptSystem->initalizeScript(index, 1);
    scriptSystem->startScript(index, 1);
}

void IEECS::shutdown()
{
    clearSystems();
}

void IEECS::onUpdateFrame()
{
    for(auto* system : qAsConst(systems))
    {
        system->onUpdateFrame(onUpdateEvent);
    }
}

IEEntity IEECS::create()
{
    IEEntity entity = entityManager->create();

    this->attachComponent(entity, IEComponentType::Name);
    this->attachComponent(entity, IEComponentType::Hierarchy);
    this->attachComponent(entity, IEComponentType::Transform);

    emit entityCreated(entity);

    return entity;
}

void IEECS::remove(const IEEntity entity)
{
    // Recursively remove child entities
    auto hierarchyComponent = this->getComponent<IEECSHierarchySystem>(IEComponentType::Hierarchy);
    int hierarchyIndex = hierarchyComponent->lookUpIndex(entity);
    auto childrenList = hierarchyComponent->getChildrenList(hierarchyIndex);
    for(auto& child : childrenList)
    {
        this->remove(child);
    }

    // Iterate through the systems, removing the entity from them
    QMapIterator<IEComponentType, IEECSSystem*> it(systems);
    while(it.hasNext())
    {
        it.next();
        detachComponent(entity, it.key());
    }

    entityManager->remove(entity);

    emit entityRemoved(entity);
}

int IEECS::attachComponent(const IEEntity entity, const IEComponentType type)
{
    if(!doesSystemExist(type))
        return -1;

    if(!entityManager->attachComponent(entity, (unsigned long long)type))
        return -1;

    return systems[type]->attach(entity);
}

bool IEECS::detachComponent(const IEEntity entity, const IEComponentType type)
{
    if(!doesSystemExist(type))
        return false;

    if(!entityManager->detachComponent(entity, (unsigned long long)type))
        return false;

    return systems[type]->detach(entity);
}

bool IEECS::hasComponent(const IEEntity entity, const IEComponentType type) const
{
    return entityManager->hasComponent(entity, (unsigned long long)type);
}

bool IEECS::doesSystemExist(const IEComponentType type) const
{
    return systems.contains(type);
}

int IEECS::entityCount() const
{
    return entityManager->count();
}

void IEECS::clearSystems()
{
    QMapIterator<IEComponentType, IEECSSystem*> it(systems);
    while(it.hasNext())
    {
        it.next();

        IEECSSystem* temp = it.value();
        systems[it.key()] = nullptr;
        delete temp;
    }

    systems.clear();
}

void IEECS::initSystems()
{
    auto nameSystem = new IEECSNameSystem();
    auto hierarchySystem = new IEECSHierarchySystem();
    auto inputSystem = new IEECSInputSystem();
    auto scriptSystem = new IEECSScriptSystem();
    auto transformSystem = new IEECSTransformSystem();
    auto cameraSystem = new IEECSCameraSystem();
    auto meshSystem = new IEECSMeshSystem();
    auto materialSystem = new IEECSMaterialSystem();
    auto shaderSystem = new IEECSShaderSystem();
    auto renderableSystem = new IEECSRenderableSystem();

    systems[IEComponentType::Name] = nameSystem;
    systems[IEComponentType::Hierarchy] = hierarchySystem;
    systems[IEComponentType::Input] = inputSystem;
    systems[IEComponentType::Script] = scriptSystem;
    systems[IEComponentType::Transform] = transformSystem;
    systems[IEComponentType::Camera] = cameraSystem;
    systems[IEComponentType::Mesh] = meshSystem;
    systems[IEComponentType::Material] = materialSystem;
    systems[IEComponentType::Shader] = shaderSystem;
    systems[IEComponentType::Renderable] = renderableSystem;
}

QDataStream& IEECS::serialize(QDataStream& out, const Serializable& obj) const
{
    const IEECS& ecs = static_cast<const IEECS&>(obj);

    out << *ecs.entityManager << (int)ecs.systems.size();

    QMapIterator<IEComponentType, IEECSSystem*> it(ecs.systems);
    while(it.hasNext())
    {
        it.next();

        out << it.key();

        switch(it.key())
        {
        case IEComponentType::Name: { out << *static_cast<IEECSNameSystem*>(it.value()); break; }
        case IEComponentType::Hierarchy: { out << *static_cast<IEECSHierarchySystem*>(it.value()); break; }
        case IEComponentType::Input: { out << *static_cast<IEECSInputSystem*>(it.value()); break; }
        case IEComponentType::Script: { out << *static_cast<IEECSScriptSystem*>(it.value()); break; }
        case IEComponentType::Physics: { break; }
        case IEComponentType::Transform: { out << *static_cast<IEECSTransformSystem*>(it.value()); break; }
        case IEComponentType::Camera: { out << *static_cast<IEECSCameraSystem*>(it.value()); break; }
        case IEComponentType::Material: { out << *static_cast<IEECSMaterialSystem*>(it.value()); break; }
        case IEComponentType::Mesh: { out << *static_cast<IEECSMeshSystem*>(it.value()); break; }
        case IEComponentType::Shader: { out << *static_cast<IEECSShaderSystem*>(it.value()); break; }
        case IEComponentType::Renderable: { out << *static_cast<IEECSRenderableSystem*>(it.value()); break; }
        default: { break; }
        }
    }

    return out;
}

QDataStream& IEECS::deserialize(QDataStream& in, Serializable& obj)
{
    IEECS& ecs = static_cast<IEECS&>(obj);

    int size = 0;

    in >> *ecs.entityManager >> size;

    IEComponentType type;
    for(int i = 0; i < size; i++)
    {
        in >> type;

        switch(type)
        {
        case IEComponentType::Name: { in >> *static_cast<IEECSNameSystem*>(ecs.systems[type]); break; }
        case IEComponentType::Hierarchy: { in >> *static_cast<IEECSHierarchySystem*>(ecs.systems[type]); break; }
        case IEComponentType::Input: { in >> *static_cast<IEECSInputSystem*>(ecs.systems[type]); break; }
        case IEComponentType::Script: { in >> *static_cast<IEECSScriptSystem*>(ecs.systems[type]); break; }
        case IEComponentType::Physics: { break; }
        case IEComponentType::Transform: { in >> *static_cast<IEECSTransformSystem*>(ecs.systems[type]); break; }
        case IEComponentType::Camera: { in >> *static_cast<IEECSCameraSystem*>(ecs.systems[type]); break; }
        case IEComponentType::Material: { in >> *static_cast<IEECSMaterialSystem*>(ecs.systems[type]); break; }
        case IEComponentType::Mesh: { in >> *static_cast<IEECSMeshSystem*>(ecs.systems[type]); break; }
        case IEComponentType::Shader: { in >> *static_cast<IEECSShaderSystem*>(ecs.systems[type]); break; }
        case IEComponentType::Renderable: { in >> *static_cast<IEECSRenderableSystem*>(ecs.systems[type]); break; }
        default: { break; }
        }
    }

    return in;
}
