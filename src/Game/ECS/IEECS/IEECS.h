#pragma once

#include <map>
#include <memory>

#include "IEObject.h"
#include "Serializable.h"
#include "IEComponentType.h"
#include "IEEntity.h"

class GameStartEvent;
class IEEntityManager;
class IEECSSystem;
class ECSOnUpdateEvent;

class IEECS : public IEObject, public Serializable
{
    Q_OBJECT

    std::unique_ptr<IEEntityManager> entityManager;
    std::map<IEComponentType, std::unique_ptr<IEECSSystem>> systems;

    std::unique_ptr<ECSOnUpdateEvent> onUpdateEvent;

public:
    IEECS();
    ~IEECS();

    void startup(const GameStartEvent& event);
    void shutdown();

    void onUpdateFrame();

    IEEntity create();
    void remove(const IEEntity entity);
    int attachComponent(const IEEntity entity, const IEComponentType type);
    bool detachComponent(const IEEntity entity, const IEComponentType type);
    bool hasComponent(const IEEntity entity, const IEComponentType type) const;
    bool doesSystemExist(const IEComponentType type) const;
    int entityCount() const;
    void clearSystems();

private:
    void initSystems();

signals:
    void entityCreated(const IEEntity entity);
    void entityRemoved(const IEEntity entity);
    void componentAttached(const IEEntity entity, const IEComponentType type);
    void componentDetached(const IEEntity entity, const IEComponentType type);

public:
    template<class T>
    T* getComponent(const IEComponentType type) const
    {
        if(!doesSystemExist(type))
            return nullptr;

        return dynamic_cast<T*>(&(*systems.at(type)));
    }

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};
