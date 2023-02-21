#pragma once

#include <QDataStream>

#include "IEObject.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"
#include "IEECS.h"

class GameStartEvent;

class IEScene : public IEObject
{
    Q_OBJECT

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

    void onUpdateFrame();

    IEMeshManager* getMeshManager() const { return meshManager; }
    IEMaterialManager* getMaterialManager() const { return materialManager; }
    IEShaderManager* getShaderManager() const { return shaderManager; }
    IERenderableManager* getRenderableManager() const { return renderableManager; }
    IEECS* getECS() const { return ecs; }

    friend QDataStream& operator<<(QDataStream& out, const IEScene& scene)
    {
        out << *scene.meshManager
            << *scene.materialManager
            << *scene.shaderManager
            << *scene.renderableManager
            << *scene.ecs;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEScene& scene)
    {
        in >> *scene.meshManager
           >> *scene.materialManager
           >> *scene.shaderManager
           >> *scene.renderableManager
           >> *scene.ecs;

        return in;
    }
};
