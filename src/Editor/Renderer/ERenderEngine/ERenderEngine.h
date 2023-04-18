#pragma once

#include "IEObject.h"

class EGridRenderable;
class ESelectedRenderable;
class EPhysicsEngine;
class IECamera;
class QOpenGLExtraFunctions;

class ERenderEngine : public IEObject
{
    Q_OBJECT

    EGridRenderable* gridRenderable;
    ESelectedRenderable* selectedRenderable;

public:
    ERenderEngine(QObject* parent = nullptr);
    ~ERenderEngine();

    void startup(EPhysicsEngine* physicsEngine);

    void onRenderPreFrame(QOpenGLExtraFunctions* glFunc);
    void onRenderFrame(QOpenGLExtraFunctions* glFunc, IECamera* camera);
};

