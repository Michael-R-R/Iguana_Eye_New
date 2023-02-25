#pragma once

#include <QDataStream>
#include <QMap>

#include "IEObject.h"
#include "IEComponentType.h"
#include "IEEntity.h"
#include "IEEntityManager.h"
#include "IEECSSystem.h"
#include "IEECSNameSystem.h"
#include "IEECSHierarchySystem.h"
#include "IEECSInputSystem.h"
#include "IEECSTransformSystem.h"
#include "IEECSMeshSystem.h"
#include "IEECSMaterialSystem.h"
#include "IEECSShaderSystem.h"
#include "IEECSRenderableSystem.h"
#include "ECSOnUpdateEvent.h"

class GameStartEvent;

class IEECS : public IEObject
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
            case IEComponentType::Name: { out << *static_cast<IEECSNameSystem*>(it.value()); break; }
            case IEComponentType::Input: { out << *static_cast<IEECSInputSystem*>(it.value()); break; }
            case IEComponentType::Transform: { out << *static_cast<IEECSTransformSystem*>(it.value()); break; }
            case IEComponentType::Camera: { break; }
            case IEComponentType::CameraController: { break; }
            case IEComponentType::Material: { out << *static_cast<IEECSMaterialSystem*>(it.value()); break; }
            case IEComponentType::Mesh: { out << *static_cast<IEECSMeshSystem*>(it.value()); break; }
            case IEComponentType::Shader: { out << *static_cast<IEECSShaderSystem*>(it.value()); break; }
            case IEComponentType::Renderable: { out << *static_cast<IEECSRenderableSystem*>(it.value()); break; }
            case IEComponentType::Physics: { break; }
            case IEComponentType::Hierarchy: { out << *static_cast<IEECSHierarchySystem*>(it.value()); break; }
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
            case IEComponentType::Name: { in >> *static_cast<IEECSNameSystem*>(ecs.systems[type]); break; }
            case IEComponentType::Input: { in >> *static_cast<IEECSInputSystem*>(ecs.systems[type]); break; }
            case IEComponentType::Transform: { in >> *static_cast<IEECSTransformSystem*>(ecs.systems[type]); break; }
            case IEComponentType::Camera: { break; }
            case IEComponentType::CameraController: { break; }
            case IEComponentType::Material: { in >> *static_cast<IEECSMaterialSystem*>(ecs.systems[type]); break; }
            case IEComponentType::Mesh: { in >> *static_cast<IEECSMeshSystem*>(ecs.systems[type]); break; }
            case IEComponentType::Shader: { in >> *static_cast<IEECSShaderSystem*>(ecs.systems[type]); break; }
            case IEComponentType::Renderable: { in >> *static_cast<IEECSRenderableSystem*>(ecs.systems[type]); break; }
            case IEComponentType::Physics: { break; }
            case IEComponentType::Hierarchy: { in >> *static_cast<IEECSHierarchySystem*>(ecs.systems[type]); break; }
            default: { break; }
            }
        }

        return in;
    }
};
