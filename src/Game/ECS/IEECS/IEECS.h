#pragma once

#include <QDataStream>
#include <QMap>

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

    ECSOnUpdateEvent* onUpdateEvent;

    IEEntityManager* entityManager;
    QMap<IEComponentType, IEECSSystem*> systems;

public:
    IEECS(QObject* parent = nullptr);
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
    template <class T>
    T* getComponent(const IEComponentType type) const
    {
        if(!doesSystemExist(type))
            return nullptr;

        return dynamic_cast<T*>(systems[type]);
    }

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) const override;
};
