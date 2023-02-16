#include "EWOpenGLViewportTime.h"
#include "EWOpenGLViewport.h"

EWOpenGLViewportTime::EWOpenGLViewportTime(const int msUpdate, const int msRender, QObject* parent) :
    IEObject(parent),
    updateTimer(new QTimer(this)),
    renderTimer(new QTimer(this)),
    updateRefresh(msUpdate), renderRefresh(msRender),
    dt()
{

}

void EWOpenGLViewportTime::startup(EWOpenGLViewport* viewport)
{
    this->setupUpdateTimer(viewport);
    this->setupRenderTimer(viewport);
    this->startUpdateTimer();
    this->startRenderTimer();
}

void EWOpenGLViewportTime::shutdown()
{
    this->stopUpdateTimer();
    this->stopRenderTimer();
}

void EWOpenGLViewportTime::startUpdateTimer()
{
    if(updateTimer->isActive()) return;
    updateTimer->start(updateRefresh);
}

void EWOpenGLViewportTime::startRenderTimer()
{
    if(renderTimer->isActive()) return;
    renderTimer->start(renderRefresh);
}

void EWOpenGLViewportTime::stopUpdateTimer()
{
    updateTimer->stop();
}

void EWOpenGLViewportTime::stopRenderTimer()
{
    renderTimer->stop();
}

void EWOpenGLViewportTime::setupUpdateTimer(EWOpenGLViewport* viewport)
{
    updateTimer->setTimerType(Qt::PreciseTimer);
    connect(updateTimer, &QTimer::timeout, this, [viewport]() { viewport->onUpdateFrame(); });
}

void EWOpenGLViewportTime::setupRenderTimer(EWOpenGLViewport* viewport)
{
    renderTimer->setTimerType(Qt::PreciseTimer);
    connect(renderTimer, &QTimer::timeout, this, [viewport]() { viewport->update(); });
}
