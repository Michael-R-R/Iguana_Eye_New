#include "ERenderEngine.h"
#include "EGridRenderable.h"
#include "IECamera.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLContext>

ERenderEngine::ERenderEngine(QObject* parent) :
    IEObject(parent),
    gridRenderable(QSharedPointer<EGridRenderable>::create())
{

}

ERenderEngine::~ERenderEngine()
{

}

void ERenderEngine::onRenderFrame(QOpenGLExtraFunctions* glFunc, QSharedPointer<IECamera> camera)
{
    gridRenderable->draw(glFunc, camera);
}
