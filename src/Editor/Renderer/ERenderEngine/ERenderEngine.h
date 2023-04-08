#pragma once

#include <QSharedPointer>

#include "IEObject.h"

class EGridRenderable;
class IECamera;
class QOpenGLExtraFunctions;

class ERenderEngine : public IEObject
{
    Q_OBJECT

    QSharedPointer<EGridRenderable> gridRenderable;

public:
    ERenderEngine(QObject* parent = nullptr);
    ~ERenderEngine();

    void onRenderFrame(QOpenGLExtraFunctions* glFunc, QSharedPointer<IECamera> camera);
};

