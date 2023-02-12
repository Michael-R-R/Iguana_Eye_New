#pragma once

#include <QTimer>

#include "IEObject.h"
#include "DeltaTime.h"

class GLViewport;

class GLTime : public IEObject
{
    Q_OBJECT

    QTimer* updateTimer;
    QTimer* renderTimer;
    int updateRefresh;
    int renderRefresh;

    DeltaTime dt;

public:
    GLTime(const int msUpdate, const int msRender, QObject* parent = nullptr);
    ~GLTime() {}

    void startup(GLViewport* viewport);
    void shutdown();

    void startUpdateTimer();
    void startRenderTimer();

    void stopUpdateTimer();
    void stopRenderTimer();

    float processDeltaTime() { return dt.processDeltaTime(); }
    float getDeltaTime() const { return dt.getDeltaTime(); }
    float getFPS() const { return dt.getFPS(); }

private:
    void setupUpdateTimer(GLViewport* viewport);
    void setupRenderTimer(GLViewport* viewport);
};
