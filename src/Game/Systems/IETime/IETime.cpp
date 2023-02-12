#include "IETime.h"
#include "ApplicationWindow.h"

IETime::IETime(const int msUpdate, const int msRender, QObject* parent) :
    IEObject(parent),
    updateTimer(new QTimer(this)),
    renderTimer(new QTimer(this)),
    updateRefresh(msUpdate), renderRefresh(msRender),
    dt()
{

}

IETime::~IETime()
{

}

void IETime::startup(const ApplicationWindow* application)
{
    this->setupUpdateTimer(application);
    this->setupRenderTimer(application);
    this->startUpdateTimer();
    this->startRenderTimer();
}

void IETime::shutdown()
{
    this->stopUpdateTimer();
    this->stopRenderTimer();
}

void IETime::startUpdateTimer()
{
    if(updateTimer->isActive()) return;
    updateTimer->start(updateRefresh);
}

void IETime::startRenderTimer()
{
    if(renderTimer->isActive()) return;
    renderTimer->start(renderRefresh);
}

void IETime::stopUpdateTimer()
{
    updateTimer->stop();
}

void IETime::stopRenderTimer()
{
    renderTimer->stop();
}

void IETime::setupUpdateTimer(const ApplicationWindow* application)
{
    updateTimer->setTimerType(Qt::PreciseTimer);
    connect(updateTimer, &QTimer::timeout, this, [application]() { application->onUpdateFrame(); });
}

void IETime::setupRenderTimer(const ApplicationWindow* application)
{
    renderTimer->setTimerType(Qt::PreciseTimer);
    connect(renderTimer, &QTimer::timeout, this, [application]() { application->onRenderFrame(); });
}
