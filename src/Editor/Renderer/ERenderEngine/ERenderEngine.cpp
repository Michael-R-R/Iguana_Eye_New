#include "ERenderEngine.h"
#include "EGridRenderable.h"
#include "IEGame.h"
#include "IECamera.h"
#include <QOpenGLExtraFunctions>

ERenderEngine::ERenderEngine(QObject* parent) :
    IEObject(parent),
    gridRenderable(nullptr)
{

}

ERenderEngine::~ERenderEngine()
{

}

void ERenderEngine::startup(IEGame&)
{
    gridRenderable = new EGridRenderable(this);
}

void ERenderEngine::onRenderFrame(QOpenGLExtraFunctions* glFunc, IECamera* camera)
{
    gridRenderable->draw(glFunc, camera);
}
