#include "IETime.h"
#include "IEGame.h"

IETime::IETime(const int msUpdate, const int msRender) :
    updateTimer(this),
    renderTimer(this),
    updateRefresh(msUpdate), renderRefresh(msRender),
    dt()
{

}

IETime::~IETime()
{

}

void IETime::startup(IEGame& game)
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

void IETime::startUpdateTimer()
{
    if(updateTimer.isActive()) return;
    updateTimer.start(updateRefresh);
}

void IETime::startRenderTimer()
{
    if(renderTimer.isActive()) return;
    renderTimer.start(renderRefresh);
}

void IETime::stopUpdateTimer()
{
    updateTimer.stop();
}

void IETime::stopRenderTimer()
{
    renderTimer.stop();
}

void IETime::setupUpdateTimer(IEGame& game)
{
    updateTimer.setTimerType(Qt::PreciseTimer);
    connect(&updateTimer, &QTimer::timeout, this, [&game]() { game.onUpdateFrame(); });
}

void IETime::setupRenderTimer(IEGame& game)
{
    renderTimer.setTimerType(Qt::PreciseTimer);
    connect(&renderTimer, &QTimer::timeout, this, [&game]() { game.update(); });
}

QDataStream& IETime::serialize(QDataStream& out, const Serializable& obj) const
{
    const IETime& time = static_cast<const IETime&>(obj);

    out << time.updateRefresh << time.renderRefresh;

    return out;
}

QDataStream& IETime::deserialize(QDataStream& in, Serializable& obj)
{
    IETime& time = static_cast<IETime&>(obj);

    in >> time.updateRefresh >> time.renderRefresh;

    return in;
}
