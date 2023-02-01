#pragma once

#include <QTimer>

#include "IEObject.h"
#include "DeltaTime.h"

class Game;

class IETime : public IEObject
{
    Q_OBJECT

    QTimer* updateTimer;
    QTimer* renderTimer;
    int updateRefresh;
    int renderRefresh;

    DeltaTime dt;

public:
    IETime(const int msUpdate, const int msRender, QObject* parent = nullptr);
    ~IETime();

    void setupUpdateTimer(Game* game);
    void setupRenderTimer(Game* game);

    void startUpdateTimer();
    void startRenderTimer();

    void stopUpdateTimer();
    void stopRenderTimer();

    void setUpdateRefresh(const int ms);
    void setRenderRefresh(const int ms);

    float processDeltaTime() { return dt.processDeltaTime(); }
    float getDeltaTime() const { return dt.getDeltaTime(); }
    float getFPS() const { return dt.getFPS(); }
};

