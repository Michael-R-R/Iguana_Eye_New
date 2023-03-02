#include "IEECS.h"
#include "GameStartEvent.h"

IEECS::IEECS(QObject* parent) :
    IEObject(parent),
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
    auto transformSystem = new IEECSTransformSystem();
    auto cameraSystem = new IEECSCameraSystem();
    auto meshSystem = new IEECSMeshSystem();
    auto materialSystem = new IEECSMaterialSystem();
    auto shaderSystem = new IEECSShaderSystem();
    auto renderableSystem = new IEECSRenderableSystem();

    systems[IEComponentType::Name] = nameSystem;
    systems[IEComponentType::Hierarchy] = hierarchySystem;
    systems[IEComponentType::Input] = inputSystem;
    systems[IEComponentType::Transform] = transformSystem;
    systems[IEComponentType::Camera] = cameraSystem;
    systems[IEComponentType::Mesh] = meshSystem;
    systems[IEComponentType::Material] = materialSystem;
    systems[IEComponentType::Shader] = shaderSystem;
    systems[IEComponentType::Renderable] = renderableSystem;
}
