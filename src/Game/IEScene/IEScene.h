#pragma once

#include <memory>

#include "IEGameSystem.h"

class IEMeshManager;
class IEMaterialManager;
class IEShaderManager;
class IERenderableManager;
class IECameraManager;

class IEScene : public IEGameSystem
{
    IEScene();
    static IEScene mInstance;

    std::unique_ptr<IEMeshManager> meshManager;
    std::unique_ptr<IEMaterialManager> materialManager;
    std::unique_ptr<IEShaderManager> shaderManager;
    std::unique_ptr<IERenderableManager> renderableManager;
    std::unique_ptr<IECameraManager> cameraManager;

public:
    static IEScene& instance();
    ~IEScene();

    void startup(IEGame& game) override;
    void shutdown(IEGame& game) override;
    void initalize(IEGame& game) override;
    void reset(IEGame& game) override;

    IEMeshManager& getMeshManager() const { return *meshManager; }
    IEMaterialManager& getMaterialManager() const { return *materialManager; }
    IEShaderManager& getShaderManager() const { return *shaderManager; }
    IERenderableManager& getRenderableManager() const { return *renderableManager; }
    IECameraManager& getCameraManager() const { return *cameraManager; }

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
