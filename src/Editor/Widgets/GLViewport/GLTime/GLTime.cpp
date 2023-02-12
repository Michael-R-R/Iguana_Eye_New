#include "GLTime.h"
#include "GLViewport.h"

GLTime::GLTime(const int msUpdate, const int msRender, QObject* parent) :
    IEObject(parent),
    updateTimer(new QTimer(this)),
    renderTimer(new QTimer(this)),
    updateRefresh(msUpdate), renderRefresh(msRender),
    dt()
{

}

void GLTime::startup(GLViewport* viewport)
{
    this->setupUpdateTimer(viewport);
    this->setupRenderTimer(viewport);
    this->startUpdateTimer();
    this->startRenderTimer();
}

void GLTime::shutdown()
{
    this->stopUpdateTimer();
    this->stopRenderTimer();
}

void GLTime::startUpdateTimer()
{
    if(updateTimer->isActive()) return;
    updateTimer->start(updateRefresh);
}

void GLTime::startRenderTimer()
{
    if(renderTimer->isActive()) return;
    renderTimer->start(renderRefresh);
}

void GLTime::stopUpdateTimer()
{
    updateTimer->stop();
}

void GLTime::stopRenderTimer()
{
    renderTimer->stop();
}

void GLTime::setupUpdateTimer(GLViewport* viewport)
{
    updateTimer->setTimerType(Qt::PreciseTimer);
    connect(updateTimer, &QTimer::timeout, this, [viewport]() { viewport->onUpdateFrame(); });
}

void GLTime::setupRenderTimer(GLViewport* viewport)
{
    renderTimer->setTimerType(Qt::PreciseTimer);
    connect(renderTimer, &QTimer::timeout, this, [viewport]() { viewport->update(); });
}
