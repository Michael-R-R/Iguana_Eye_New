#pragma once

#include <QSharedPointer>

#include "IEGameSystem.h"

class IEMeshManager;
class IEMaterialManager;
class IEShaderManager;
class IERenderableManager;
class IECameraManager;

class IEScene : public IEGameSystem
{
    QSharedPointer<IEMeshManager> meshManager;
    QSharedPointer<IEMaterialManager> materialManager;
    QSharedPointer<IEShaderManager> shaderManager;
    QSharedPointer<IERenderableManager> renderableManager;
    QSharedPointer<IECameraManager> cameraManager;

public:
    IEScene();
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
