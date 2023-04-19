#pragma once

#include "IEObject.h"

class EGridRenderable;
class IEGame;
class IECamera;
class QOpenGLExtraFunctions;

class ERenderEngine : public IEObject
{
    Q_OBJECT

    EGridRenderable* gridRenderable;

public:
    ERenderEngine(QObject* parent = nullptr);
    ~ERenderEngine();

    void startup(IEGame& game);
    void onRenderFrame(QOpenGLExtraFunctions* glFunc, IECamera* camera);
};

