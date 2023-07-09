#include "IEECSTransformSystem.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEECS.h"
#include "IEECSHierarchySystem.h"
#include "IEECSRenderableSystem.h"
#include "IERenderableManager.h"
#include "IERenderable.h"
#include <glm/gtc/matrix_transform.hpp>

IEECSTransformSystem::IEECSTransformSystem(QObject* parent) :
    IEECSSystem(typeid(IEECSTransformSystem).hash_code(), parent),
    data(),
    dirtyParentIndices()
{
    IEECSTransformSystem::attach(IEEntity(-1));
}

IEECSTransformSystem::~IEECSTransformSystem()
{

}

int IEECSTransformSystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    int index = entityMap.size();

    entityMap[entity] = index;
    dirtyParentIndices.insert(index);

    data.entity.append(entity);
    data.position.append(glm::vec3(0.0f, 0.0f, 0.0f));
    data.rotation.append(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
    data.scale.append(glm::vec3(1.0f, 1.0f, 1.0f));
    data.transform.append(glm::mat4(1.0f));

    return index;
}

bool IEECSTransformSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    int indexToRemove = entityMap[entity];

    int lastIndex = entityMap.size() - 1;
    IEEntity lastEntity = data.entity[lastIndex];

    data.entity[indexToRemove] = data.entity[lastIndex];
    data.position[indexToRemove] = data.position[lastIndex];
    data.rotation[indexToRemove] = data.rotation[lastIndex];
    data.scale[indexToRemove] = data.scale[lastIndex];
    data.transform[indexToRemove] = data.transform[lastIndex];

    data.entity.removeLast();
    data.position.removeLast();
    data.rotation.removeLast();
    data.scale.removeLast();
    data.transform.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    dirtyParentIndices.remove(indexToRemove);

    return true;
}

void IEECSTransformSystem::startUp(const IEGame& game)
{
    auto* ecs = game.getSystem<IEECS>();
    hSystem = ecs->getComponent<IEECSHierarchySystem>();
    rSystem = ecs->getComponent<IEECSRenderableSystem>();
    renderableManager = game.getSystem<IEScene>()->getManager<IERenderableManager>();
}

void IEECSTransformSystem::shutdown(const IEGame&)
{
    hSystem = nullptr;
    rSystem = nullptr;
    renderableManager = nullptr;
}

void IEECSTransformSystem::onUpdateFrame()
{
    for(const auto& i : qAsConst(dirtyParentIndices))
    {
        QSet<int> dirtyChildIndices;
        updateTransform(i, dirtyChildIndices);

        for(const auto& j : qAsConst(dirtyChildIndices))
        {
            const IEEntity& childEntity = data.entity[j];
            const int childIndex = rSystem->lookUpIndex(childEntity);
            const uint64_t renderableId = rSystem->getResourceId(childIndex);
            auto renderable = renderableManager->value<IERenderable>(renderableId);
            if(!renderable)
                continue;

            glm::mat4& transform = data.transform[j];
            // TODO implement
        }

        const IEEntity& parentEntity = data.entity[i];
        const int parentIndex = rSystem->lookUpIndex(parentEntity);
        const uint64_t renderableId = rSystem->getResourceId(parentIndex);
        auto renderable = renderableManager->value<IERenderable>(renderableId);
        if(!renderable)
            continue;

        glm::mat4& transform = data.transform[i];
        // TODO implement
    }

    dirtyParentIndices.clear();
}

const glm::vec3& IEECSTransformSystem::getPosition(const int index) const
{
    if(!indexBoundCheck(index))
        return data.position[0];

    return data.position[index];
}

const glm::vec4& IEECSTransformSystem::getRotation(const int index) const
{
    if(!indexBoundCheck(index))
        return data.rotation[0];

    return data.rotation[index];
}

const glm::vec3& IEECSTransformSystem::getScale(const int index) const
{
    if(!indexBoundCheck(index))
        return data.scale[0];

    return data.scale[index];
}

const glm::mat4& IEECSTransformSystem::getTransform(const int index) const
{
    if(!indexBoundCheck(index))
        return data.transform[0];

    return data.transform[index];
}

void IEECSTransformSystem::setPosition(const int index, const glm::vec3& val)
{
    if(!indexBoundCheck(index))
        return;

    data.position[index] = val;

    dirtyParentIndices.insert(index);
}

void IEECSTransformSystem::setRotation(const int index, const glm::vec3& val)
{
    if(!indexBoundCheck(index))
        return;

    data.rotation[index] = glm::vec4(val[0], val[1], val[2], 0.0f);

    dirtyParentIndices.insert(index);
}

void IEECSTransformSystem::setRotation(const int index, const glm::vec4& val)
{
    if(!indexBoundCheck(index))
        return;

    data.rotation[index] = val;

    dirtyParentIndices.insert(index);
}

void IEECSTransformSystem::setScale(const int index, const glm::vec3& val)
{
    if(!indexBoundCheck(index))
        return;

    data.scale[index] = val;

    dirtyParentIndices.insert(index);
}

void IEECSTransformSystem::updateTransform(const int index,
                                           QSet<int>& dirtyChildren)
{
    if(!indexBoundCheck(index))
        return;

    IEEntity entity = data.entity[index];

    int hierarchyIndex = hSystem->lookUpIndex(entity);
    IEEntity parentEntity = hSystem->getParent(hierarchyIndex);
    int parentTransformIndex = this->lookUpIndex(parentEntity);

    if(parentTransformIndex > 0)
    {
        // Update child relative to parent
        data.transform[index] = data.transform[parentTransformIndex] * calcModelMatrix(index);
        dirtyChildren.insert(index);
    }
    else
    {
        // Update parent
        data.transform[index] = calcModelMatrix(index);
    }

    for(auto& childEntity : hSystem->getChildrenList(hierarchyIndex))
    {
        int childIndex = this->lookUpIndex(childEntity);
        this->updateTransform(childIndex, dirtyChildren);
    }
}

glm::mat4 IEECSTransformSystem::calcModelMatrix(const int index)
{
    if(!indexBoundCheck(index))
        return glm::mat4();

    auto& pos = data.position[index];
    auto& rot = data.rotation[index];
    auto& scl = data.scale[index];

    glm::mat4 model(1.0f);
    model = glm::translate(model, pos);
    model = glm::rotate(model, glm::radians(rot[3]), glm::vec3(rot));
    model = glm::scale(model, scl);

    return model;
}

QDataStream& IEECSTransformSystem::serialize(QDataStream& out, const IESerializable& obj) const
{
    const auto& system = static_cast<const IEECSTransformSystem&>(obj);

    out << system.entityMap << system.data;

    return out;
}

QDataStream& IEECSTransformSystem::deserialize(QDataStream& in, IESerializable& obj)
{
    auto& system = static_cast<IEECSTransformSystem&>(obj);

    in >> system.entityMap >> system.data;

    return in;
}
