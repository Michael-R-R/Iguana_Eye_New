#pragma once

#include <QDataStream>
#include <QMap>

#include "IEObject.h"
#include "IEComponentType.h"
#include "IEEntity.h"
#include "IEEntityManager.h"
#include "IEECSSystem.h"
#include "IEECSInputSystem.h"

class GameStartEvent;

class IEECS : public IEObject
{
    Q_OBJECT

    IEEntityManager* entityManager;
    QMap<IEComponentType, IEECSSystem*> systems;

public:
    IEECS(QObject* parent = nullptr);
    ~IEECS();

    void startup(const GameStartEvent& event);
    void shutdown();

    IEEntity create();
    void remove(const IEEntity entity);
    int attachComponent(const IEEntity entity, const IEComponentType type);
    bool detachComponent(const IEEntity entity, const IEComponentType type);
    bool hasComponent(const IEEntity entity, const IEComponentType type);
    bool doesSystemExist(const IEComponentType type);
    void clearSystems();

    IEEntityManager* getEntityManager() const { return entityManager; }
    const QMap<IEComponentType, IEECSSystem*>& getSystems() const { return systems; }

    void setEntityManager(IEEntityManager* val) { entityManager = val; }
    void setSystems(const QMap<IEComponentType, IEECSSystem*>& val) { systems = val; }

private:
    void initSystems();

public:
    template <class T>
    T* getComponent(const IEComponentType type)
    {
        if(!doesSystemExist(type))
            return nullptr;

        return dynamic_cast<T*>(systems[type]);
    }

signals:
    void entityCreated(const IEEntity entity);
    void entityRemoved(const IEEntity entity);
    void componentAttached(const IEEntity entity, const IEComponentType type);
    void componentDetached(const IEEntity entity, const IEComponentType type);
};

QDataStream& operator<<(QDataStream& out, const IEECS& ecs);
QDataStream& operator>>(QDataStream& in, IEECS& ecs);
