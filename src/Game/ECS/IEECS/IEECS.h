#pragma once

#include <QMap>
#include <QSharedPointer>

#include "IEGameSystem.h"
#include "IEEntityManager.h"
#include "IEEntity.h"

class IEGame;
class IEECSSystem;
class ECSOnUpdateEvent;

class IEECS : public IEGameSystem
{
    Q_OBJECT

    QMap<size_t, IEECSSystem*> systems;
    IEEntityManager* entityManager;

public:
    IEECS(QObject* parent = nullptr);
    ~IEECS();

    void startup(IEGame& game) override;
    void shutdown(IEGame& game) override;
    void initalize(IEGame& game) override;
    void reset(IEGame& game) override;

    void onUpdateFrame(ECSOnUpdateEvent& event);

    IEEntity create();
    void remove(const IEEntity entity);
    int entityCount() const;
    void clearSystems();

private:
    void initSystems();
    bool detachComponent(const IEEntity entity, const size_t& component);
    bool doesSystemExist(const size_t& component) const;

signals:
    void entityCreated(const IEEntity& entity);
    void entityRemoved(const IEEntity& entity);
    void componentAttached(const IEEntity& entity, const size_t& component);
    void componentDetached(const IEEntity& entity, const size_t& component);

public:
    template<class T>
    int attachComponent(const IEEntity entity)
    {
        size_t component = typeid(T).hash_code();

        if(!doesSystemExist(component))
            return -1;

        if(!entityManager->attachComponent(entity, component))
            return -1;

        emit componentAttached(entity, component);

        return systems[component]->attach(entity);
    }

    template<class T>
    bool detachComponent(const IEEntity entity)
    {
        size_t component = typeid(T).hash_code();

        return IEECS::detachComponent(entity, component);
    }

    template<class T>
    bool hasComponent(const IEEntity entity) const
    {
        size_t component = typeid(T).hash_code();

        return entityManager->hasComponent(entity, component);
    }

    template<class T>
    T* getComponent() const
    {
        size_t component = typeid(T).hash_code();

        if(!doesSystemExist(component))
            return nullptr;

        return static_cast<T*>(&(*systems[component]));
    }

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};
