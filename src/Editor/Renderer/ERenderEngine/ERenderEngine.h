#pragma once

#include <memory>

#include "IEObject.h"

class EGridRenderable;
class IECamera;
class QOpenGLExtraFunctions;

class ERenderEngine : public IEObject
{
    Q_OBJECT

    std::unique_ptr<EGridRenderable> gridRenderable;

public:
    ERenderEngine(QObject* parent = nullptr);
    ~ERenderEngine();

    void onRenderFrame(QOpenGLExtraFunctions* glFunc, IECamera* camera);
};

