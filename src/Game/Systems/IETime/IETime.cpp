#include "IETime.h"
#include "Game.h"

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

void IETime::startup(Game* game)
{
    this->setupUpdateTimer(game);
    this->setupRenderTimer(game);
    this->startUpdateTimer();
    this->startRenderTimer();
}

void IETime::shutdown()
{
    this->stopUpdateTimer();
    this->stopRenderTimer();
}

void IETime::setupUpdateTimer(Game* game)
{
    updateTimer->setTimerType(Qt::PreciseTimer);
    connect(updateTimer, &QTimer::timeout, this, [game]() { game->onUpdateFrame(); });
}

void IETime::setupRenderTimer(Game* game)
{
    renderTimer->setTimerType(Qt::PreciseTimer);
    connect(renderTimer, &QTimer::timeout, this, [game]() { game->update(); });
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
