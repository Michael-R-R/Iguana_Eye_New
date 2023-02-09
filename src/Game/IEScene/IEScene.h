#pragma once

#include <QDataStream>

#include "IEObject.h"
#include "IENameManager.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"
#include "IEECS.h"

class GameStartEvent;

class IEScene : public IEObject
{
    Q_OBJECT

    IENameManager* nameManager;
    IEMeshManager* meshManager;
    IEMaterialManager* materialManager;
    IEShaderManager* shaderManager;
    IERenderableManager* renderableManager;
    IEECS* ecs;

public:
    IEScene(QObject* parent = nullptr);
    ~IEScene();

    void startup(const GameStartEvent& event);
    void shutdown();

    const IENameManager* getNameManager() const { return nameManager; }
    const IEMeshManager* getMeshManager() const { return meshManager; }
    const IEMaterialManager* getMaterialManager() const { return materialManager; }
    const IEShaderManager* getShaderManager() const { return shaderManager; }
    const IERenderableManager* getRenderableManager() const { return renderableManager; }
    const IEECS* getECS() const { return ecs; }

    friend QDataStream& operator<<(QDataStream& out, const IEScene& scene)
    {
        out << *scene.nameManager
            << *scene.meshManager
            << *scene.materialManager
            << *scene.shaderManager
            << *scene.renderableManager
            << *scene.ecs;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEScene& scene)
    {
        in >> *scene.nameManager
           >> *scene.meshManager
           >> *scene.materialManager
           >> *scene.shaderManager
           >> *scene.renderableManager
           >> *scene.ecs;

        return in;
    }
};
