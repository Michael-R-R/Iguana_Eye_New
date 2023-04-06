#pragma once

#include <map>
#include <memory>

#include "IEObject.h"
#include "Serializable.h"
#include "IEEntity.h"

class IEGame;
class IEEntityManager;
class IEECSSystem;

class IEECS : public IEObject, public Serializable
{
    Q_OBJECT

    std::map<QString, std::unique_ptr<IEECSSystem>> systems;
    std::unique_ptr<IEEntityManager> entityManager;

public:
    IEECS(IEGame& game);
    ~IEECS();

    void play(IEGame& game);
    void stop(IEGame& game);

    IEEntity create();
    void remove(const IEEntity entity);
    int attachComponent(const IEEntity entity, const QString& component);
    bool detachComponent(const IEEntity entity, const QString& component);
    bool hasComponent(const IEEntity entity, const QString& component) const;
    bool doesSystemExist(const QString& component) const;
    int entityCount() const;
    void clearSystems();

private:
    void initSystems(IEGame& game);

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

        return dynamic_cast<T*>(&(*systems.at(component)));
    }

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};
