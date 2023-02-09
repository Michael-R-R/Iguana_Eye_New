#pragma once

#include <QDataStream>
#include <QVector>

#include "IEObject.h"
#include "IEEntityManager.h"
#include "IEEntity.h"
#include "IEComponentType.h"

class IEECS : public IEObject
{
    Q_OBJECT

    IEEntityManager* entityManager;

public:
    IEECS(QObject* parent = nullptr);
    ~IEECS();

    void startup();
    void shutdown();

    IEEntity create();
    void remove(const IEEntity entity);
    int attachComponent(const IEEntity entity, const IEComponentType type);
    bool detachComponent(const IEEntity entity, const IEComponentType type);
    bool hasComponent(const IEEntity entity, const IEComponentType type);

    IEEntityManager* getEntityManager() const { return entityManager; }
    void setEntityManager(IEEntityManager* val) { entityManager = val; }

signals:
    void entityCreated(const IEEntity entity);
    void entityRemoved(const IEEntity entity);
    void componentAttached(const IEEntity entity, const IEComponentType type);
    void componentDetached(const IEEntity entity, const IEComponentType type);
};

QDataStream& operator<<(QDataStream& out, const IEECS& ecs);
QDataStream& operator>>(QDataStream& in, IEECS& ecs);
