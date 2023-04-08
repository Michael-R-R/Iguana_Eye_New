#pragma once

#include <QMap>
#include <QSharedPointer>

#include "IEGameSystem.h"
#include "IEEntity.h"

class IEGame;
class IEEntityManager;
class IEECSSystem;

class IEECS : public IEGameSystem
{
    Q_OBJECT

    IEECS();
    static IEECS mInstance;

    QMap<QString, QSharedPointer<IEECSSystem>> systems;
    QSharedPointer<IEEntityManager> entityManager;

public:
    static IEECS& instance();
    ~IEECS();

    void startup(IEGame& game) override;
    void shutdown(IEGame& game) override;
    void initalize(IEGame& game) override;
    void reset(IEGame& game) override;

    IEEntity create();
    void remove(const IEEntity entity);
    int attachComponent(const IEEntity entity, const QString& component);
    bool detachComponent(const IEEntity entity, const QString& component);
    bool hasComponent(const IEEntity entity, const QString& component) const;
    bool doesSystemExist(const QString& component) const;
    int entityCount() const;
    void clearSystems();

private:
    void initSystems();

signals:
    void entityCreated(const IEEntity& entity);
    void entityRemoved(const IEEntity& entity);
    void componentAttached(const IEEntity& entity, const QString& component);
    void componentDetached(const IEEntity& entity, const QString& component);

public:
    template<class T>
    T* getComponent(const QString& component) const
    {
        if(!doesSystemExist(component))
            return nullptr;

        return dynamic_cast<T*>(&(*systems[component]));
    }

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};
