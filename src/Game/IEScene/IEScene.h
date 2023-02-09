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

    IENameManager* getNameManager() const { return nameManager; }
    IEMeshManager* getMeshManager() const { return meshManager; }
    IEMaterialManager* getMaterialManager() const { return materialManager; }
    IEShaderManager* getShaderManager() const { return shaderManager; }
    IERenderableManager* getRenderableManager() const { return renderableManager; }
    IEECS* getECS() const { return ecs; }

    void setNameManager(IENameManager* val) { nameManager = val; }
    void setMeshManager(IEMeshManager* val) { meshManager = val; }
    void setMaterialManager(IEMaterialManager* val) { materialManager = val; }
    void setShaderManager(IEShaderManager* val) { shaderManager = val; }
    void setRenderableManager(IERenderableManager* val) { renderableManager = val; }
    void setECS(IEECS* val) { ecs = val; }
};

QDataStream& operator<<(QDataStream& out, const IEScene& scene);
QDataStream& operator>>(QDataStream& in, IEScene& scene);
