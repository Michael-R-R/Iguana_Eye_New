#include "ERenderEngine.h"
#include "EGridRenderable.h"
#include "IECamera.h"
#include <QOpenGLExtraFunctions>
#include <QOpenGLContext>

ERenderEngine::ERenderEngine(QObject* parent) :
    IEObject(parent),
    gridRenderable(std::make_unique<EGridRenderable>())
{

}

ERenderEngine::~ERenderEngine()
{

}

void ERenderEngine::onRenderFrame(QOpenGLExtraFunctions* glFunc, IECamera* camera)
{
    gridRenderable->draw(glFunc, camera);
}
