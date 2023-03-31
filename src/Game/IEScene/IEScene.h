#pragma once

#include <memory>

#include "IEObject.h"
#include "Serializable.h"

class IEMeshManager;
class IEMaterialManager;
class IEShaderManager;
class IERenderableManager;
class IECameraManager;

class IEScene : public IEObject, public Serializable
{
    std::unique_ptr<IEMeshManager> meshManager;
    std::unique_ptr<IEMaterialManager> materialManager;
    std::unique_ptr<IEShaderManager> shaderManager;
    std::unique_ptr<IERenderableManager> renderableManager;
    std::unique_ptr<IECameraManager> cameraManager;

public:
    IEScene();
    ~IEScene();

    IEMeshManager& getMeshManager() const { return *meshManager; }
    IEMaterialManager& getMaterialManager() const { return *materialManager; }
    IEShaderManager& getShaderManager() const { return *shaderManager; }
    IERenderableManager& getRenderableManager() const { return *renderableManager; }
    IECameraManager& getCameraManager() const { return *cameraManager; }

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
