#pragma once

#include <QHash>

#include "IESystem.h"
#include "IEEntityManager.h"
#include "IEECSSystem.h"
#include "IEEntity.h"

class IEGame;

class IEECS : public IESystem
{
    Q_OBJECT

    QVector<IEECSSystem*> systems;
    QHash<size_t, int> systemIndex;
    IEEntityManager* entityManager;

public:
    IEECS(QObject* parent = nullptr);
    virtual ~IEECS();

    void startup(IEGame& game) override;
    void shutdown(IEGame& game) override;
    void onSerialize(IEGame& game) override;
    void onDeserialize(IEGame& game) override;
    void onUpdateFrame() override;

    IEEntity create();
    bool remove(const IEEntity entity);
    int entityCount() const;

    bool appendSystem(IEECSSystem* system);
    void clearSystems();

private:
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
        size_t key = typeid(T).hash_code();

        if(!doesSystemExist(key))
            return -1;

        if(!entityManager->attachComponent(entity, key))
            return -1;

        emit componentAttached(entity, key);

        return systems[systemIndex[key]]->attach(entity);
    }

    template<class T>
    bool detachComponent(const IEEntity entity)
    {
        size_t key = typeid(T).hash_code();

        return IEECS::detachComponent(entity, key);
    }

    template<class T>
    bool hasComponent(const IEEntity entity) const
    {
        size_t key = typeid(T).hash_code();

        return entityManager->hasComponent(entity, key);
    }

    template<class T>
    T* getComponent() const
    {
        size_t key = typeid(T).hash_code();

        if(!doesSystemExist(key))
            return nullptr;

        return static_cast<T*>(systems[systemIndex[key]]);
    }

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};
