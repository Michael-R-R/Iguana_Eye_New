#pragma once

#include <QTimer>

#include "IEObject.h"
#include "Serializable.h"
#include "DeltaTime.h"

class IEGame;

class IETime : public IEObject, public Serializable
{
    Q_OBJECT

    QTimer updateTimer;
    QTimer renderTimer;
    int updateRefresh;
    int renderRefresh;

    DeltaTime dt;

public:
    IETime(const int msUpdate, const int msRender, IEGame& game);
    ~IETime();

    void startup();
    void shutdown();

    void startUpdateTimer();
    void startRenderTimer();

    void stopUpdateTimer();
    void stopRenderTimer();

    float processDeltaTime() { return dt.processDeltaTime(); }
    float getDeltaTime() const { return dt.getDeltaTime(); }
    float getFPS() const { return dt.getFPS(); }

    int getUpdateRefresh() const { return updateRefresh; }
    int getRenderRefresh() const { return renderRefresh; }
    void setUpdateRefresh(const int ms) { updateRefresh = ms; }
    void setRenderRefresh(const int ms) { renderRefresh = ms; }

private:
    void setupUpdateTimer(IEGame& game);
    void setupRenderTimer(IEGame& game);

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
