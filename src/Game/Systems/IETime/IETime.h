#pragma once

#include <QTimer>

#include "IEGameSystem.h"
#include "DeltaTime.h"

class IETime : public IEGameSystem
{
    QTimer updateTimer;
    QTimer renderTimer;
    int updateRefresh;
    int renderRefresh;

    DeltaTime dt;

public:
    IETime(QObject* parent = nullptr);
    ~IETime();

    void startup(IEGame& game) override;
    void shutdown(IEGame& game) override;
    void initalize(IEGame& game) override;
    void reset(IEGame& game) override;

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
