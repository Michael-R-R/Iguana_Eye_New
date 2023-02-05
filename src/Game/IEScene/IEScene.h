#pragma once

#include <QDataStream>

#include "IEObject.h"
#include "IENameManager.h"
#include "IEShaderManager.h"
#include "IEMeshManager.h"

class IEScene : public IEObject
{
    Q_OBJECT

    IENameManager* nameManager;
    IEMeshManager* meshManager;
    IEShaderManager* shaderManager;

public:
    IEScene(QObject* parent = nullptr);
    ~IEScene();

    void startup();
    void shutdown();

    IENameManager* getNameManager() const { return nameManager; }
    IEMeshManager* getMeshManager() const { return meshManager; }
    IEShaderManager* getShaderManager() const { return shaderManager; }

    void setNameManager(IENameManager* val) { nameManager = val; }
    void setMeshManager(IEMeshManager* val) { meshManager = val; }
    void setShaderManager(IEShaderManager* val) { shaderManager = val; }
};

QDataStream& operator<<(QDataStream& out, const IEScene& scene);
QDataStream& operator>>(QDataStream& in, IEScene& scene);
