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

void IETime::setupUpdateTimer(Game* game)
{
    updateTimer->setTimerType(Qt::PreciseTimer);
    connect(updateTimer, &QTimer::timeout, game, &Game::onUpdateFrame);
}

void IETime::setupRenderTimer(Game* game)
{
    renderTimer->setTimerType(Qt::PreciseTimer);
    connect(renderTimer, &QTimer::timeout, game, &Game::onRenderFrame);
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

QDataStream& operator<<(QDataStream& out, const IETime& time)
{
    out << time.getUpdateRefresh() << time.getRenderRefresh();

    return out;
}

QDataStream& operator>>(QDataStream& in, IETime& time)
{
    int updateRefresh = 0;
    int renderRefresh = 0;

    in >> updateRefresh >> renderRefresh;

    time.setUpdateRefresh(updateRefresh);
    time.setRenderRefresh(renderRefresh);

    return in;
}
