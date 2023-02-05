#pragma once

#include <QDataStream>

#include "IEObject.h"
#include "IENameManager.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"

class IEScene : public IEObject
{
    Q_OBJECT

    IENameManager* nameManager;
    IEMeshManager* meshManager;
    IEMaterialManager* materialManager;
    IEShaderManager* shaderManager;

public:
    IEScene(QObject* parent = nullptr);
    ~IEScene();

    void startup();
    void shutdown();

    IENameManager* getNameManager() const { return nameManager; }
    IEMeshManager* getMeshManager() const { return meshManager; }
    IEMaterialManager* getMaterialManager() const { return materialManager; }
    IEShaderManager* getShaderManager() const { return shaderManager; }

    void setNameManager(IENameManager* val) { nameManager = val; }
    void setMeshManager(IEMeshManager* val) { meshManager = val; }
    void setMaterialManager(IEMaterialManager* val) { materialManager = val; }
    void setShaderManager(IEShaderManager* val) { shaderManager = val; }
};

QDataStream& operator<<(QDataStream& out, const IEScene& scene);
QDataStream& operator>>(QDataStream& in, IEScene& scene);
