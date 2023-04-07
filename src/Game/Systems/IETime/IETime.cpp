#include "IETime.h"
#include "IEGame.h"

IETime IETime::mInstance;
IETime& IETime::instance() { return mInstance; }

IETime::IETime() :
    updateTimer(this),
    renderTimer(this),
    updateRefresh(16), renderRefresh(16),
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

void IETime::shutdown(IEGame& game)
{
    disconnect(&updateTimer, &QTimer::timeout, &game, &IEGame::onUpdateFrame);
    disconnect(&renderTimer, &QTimer::timeout, &game, &IEGame::onRenderFrame);

    this->stopUpdateTimer();
    this->stopRenderTimer();
}

void IETime::initalize(IEGame&)
{

}

void IETime::reset(IEGame& game)
{
    shutdown(game);
    startup(game);
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
