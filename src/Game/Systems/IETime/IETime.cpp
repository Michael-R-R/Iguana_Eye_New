#include "IETime.h"
#include "IEGame.h"

IETime::IETime(const int msUpdate, const int msRender, IEGame& game) :
    updateTimer(this),
    renderTimer(this),
    updateRefresh(msUpdate), renderRefresh(msRender),
    dt()
{
    this->setupUpdateTimer(game);
    this->setupRenderTimer(game);
}

IETime::~IETime()
{

}

void IETime::startup()
{
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
    connect(&updateTimer, &QTimer::timeout, &game, &IEGame::onUpdateFrame);
}

void IETime::setupRenderTimer(IEGame& game)
{
    renderTimer.setTimerType(Qt::PreciseTimer);
    connect(&renderTimer, &QTimer::timeout, &game, &IEGame::onRenderFrame);
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
