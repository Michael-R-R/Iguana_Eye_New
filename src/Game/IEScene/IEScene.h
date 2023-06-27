#pragma once

#include "IEGameSystem.h"

class IEMeshManager;
class IEMaterialManager;
class IEShaderManager;
class IERenderableManager;
class IECameraManager;

class IEScene : public IEGameSystem
{
    IEMeshManager* meshManager;
    IEMaterialManager* materialManager;
    IEShaderManager* shaderManager;
    IERenderableManager* renderableManager;
    IECameraManager* cameraManager;

public:
    IEScene(QObject* parent = nullptr);
    ~IEScene();

    void startup(IEGame& game) override;
    void shutdown(IEGame& game) override;
    void onSerialize(IEGame& game) override;
    void onDeserialize(IEGame& game) override;

    IEMeshManager* getMeshManager() const { return meshManager; }
    IEMaterialManager* getMaterialManager() const { return materialManager; }
    IEShaderManager* getShaderManager() const { return shaderManager; }
    IERenderableManager* getRenderableManager() const { return renderableManager; }
    IECameraManager* getCameraManager() const { return cameraManager; }

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
