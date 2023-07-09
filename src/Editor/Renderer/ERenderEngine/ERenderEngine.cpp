#include "ERenderEngine.h"
#include "EGridRenderable.h"
#include "IEGame.h"
#include "IECamera.h"

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

void ERenderEngine::onRenderFrame(IECamera* camera)
{
    gridRenderable->draw(camera);
}
