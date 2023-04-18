#include "ERenderEngine.h"
#include "EGridRenderable.h"
#include "ESelectedRenderable.h"
#include "EPhysicsEngine.h"
#include "IECamera.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLContext>

ERenderEngine::ERenderEngine(QObject* parent) :
    IEObject(parent),
    gridRenderable(nullptr),
    selectedRenderable(nullptr)
{

}

ERenderEngine::~ERenderEngine()
{

}

void ERenderEngine::startup(EPhysicsEngine* physicsEngine)
{
    gridRenderable = new EGridRenderable(this);
    selectedRenderable = new ESelectedRenderable(physicsEngine, this);
}

void ERenderEngine::onRenderPreFrame(QOpenGLExtraFunctions* glFunc)
{
    selectedRenderable->predraw(glFunc);
}

void ERenderEngine::onRenderFrame(QOpenGLExtraFunctions* glFunc, IECamera* camera)
{
    selectedRenderable->draw(glFunc, camera);
    gridRenderable->draw(glFunc, camera);
}
