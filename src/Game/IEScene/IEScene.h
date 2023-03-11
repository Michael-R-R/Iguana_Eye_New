#pragma once

#include <QDataStream>

#include "IEObject.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"
#include "IECameraManager.h"
#include "IEECS.h"

class GameStartEvent;

class IEScene : public IEObject
{
    Q_OBJECT

    IEMeshManager* meshManager;
    IEMaterialManager* materialManager;
    IEShaderManager* shaderManager;
    IERenderableManager* renderableManager;
    IECameraManager* cameraManager;
    IEECS* ecs;

public:
    IEScene();
    ~IEScene();

    void startup(const GameStartEvent& event);
    void shutdown();

    void onUpdateFrame();

    IEMeshManager* getMeshManager() const { return meshManager; }
    IEMaterialManager* getMaterialManager() const { return materialManager; }
    IEShaderManager* getShaderManager() const { return shaderManager; }
    IERenderableManager* getRenderableManager() const { return renderableManager; }
    IECameraManager* getCameraManager() const { return cameraManager; }
    IEECS* getECS() const { return ecs; }

    friend QDataStream& operator<<(QDataStream& out, const IEScene& scene)
    {
        out << *scene.meshManager
            << *scene.materialManager
            << *scene.shaderManager
            << *scene.renderableManager
            << *scene.cameraManager
            << *scene.ecs;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEScene& scene)
    {
        in >> *scene.meshManager
           >> *scene.materialManager
           >> *scene.shaderManager
           >> *scene.renderableManager
           >> *scene.cameraManager
           >> *scene.ecs;

        return in;
    }
};
