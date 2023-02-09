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

private:
    void initSystems();

signals:
    void entityCreated(const IEEntity entity);
    void entityRemoved(const IEEntity entity);
    void componentAttached(const IEEntity entity, const IEComponentType type);
    void componentDetached(const IEEntity entity, const IEComponentType type);

public:
    template <class T>
    T* getComponent(const IEComponentType type)
    {
        if(!doesSystemExist(type))
            return nullptr;

        return dynamic_cast<T*>(systems[type]);
    }

    friend QDataStream& operator<<(QDataStream& out, const IEECS& ecs)
    {
        out << *ecs.entityManager << (int)ecs.systems.size();

        QMapIterator<IEComponentType, IEECSSystem*> it(ecs.systems);
        while(it.hasNext())
        {
            it.next();

            out << it.key();

            switch(it.key())
            {
            case IEComponentType::Input: { out << *static_cast<IEECSInputSystem*>(it.value()); break; }
            case IEComponentType::Transform: { break; }
            case IEComponentType::Camera: { break; }
            case IEComponentType::CameraController: { break; }
            case IEComponentType::Material: { break; }
            case IEComponentType::Mesh: { break; }
            case IEComponentType::Shader: { break; }
            case IEComponentType::Renderable: { break; }
            case IEComponentType::Physics: { break; }
            case IEComponentType::Hierarchy: { break; }
            default: { break; }
            }
        }

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEECS& ecs)
    {
        int size = 0;

        in >> *ecs.entityManager >> size;

        IEComponentType type;
        for(int i = 0; i < size; i++)
        {
            in >> type;

            switch(type)
            {
            case IEComponentType::Input: { in >> *static_cast<IEECSInputSystem*>(ecs.systems[type]); break; }
            case IEComponentType::Transform: { break; }
            case IEComponentType::Camera: { break; }
            case IEComponentType::CameraController: { break; }
            case IEComponentType::Material: { break; }
            case IEComponentType::Mesh: { break; }
            case IEComponentType::Shader: { break; }
            case IEComponentType::Renderable: { break; }
            case IEComponentType::Physics: { break; }
            case IEComponentType::Hierarchy: { break; }
            default: { break; }
            }
        }

        return in;
    }
};
