#pragma once

#include "IEObject.h"
#include "Serializable.h"

class GameStartEvent;
class IEMeshManager;
class IEMaterialManager;
class IEShaderManager;
class IERenderableManager;
class IECameraManager;
class IEECS;

class IEScene : public IEObject, public Serializable
{
    Q_OBJECT

    std::unique_ptr<IEMeshManager> meshManager;
    std::unique_ptr<IEMaterialManager> materialManager;
    std::unique_ptr<IEShaderManager> shaderManager;
    std::unique_ptr<IERenderableManager> renderableManager;
    std::unique_ptr<IECameraManager> cameraManager;
    std::unique_ptr<IEECS> ecs;

public:
    IEScene();
    ~IEScene();

    void startup(const GameStartEvent& event);
    void shutdown();

    void onUpdateFrame();

    IEMeshManager& getMeshManager() const { return *meshManager; }
    IEMaterialManager& getMaterialManager() const { return *materialManager; }
    IEShaderManager& getShaderManager() const { return *shaderManager; }
    IERenderableManager& getRenderableManager() const { return *renderableManager; }
    IECameraManager& getCameraManager() const { return *cameraManager; }
    IEECS& getECS() const { return *ecs; }

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
