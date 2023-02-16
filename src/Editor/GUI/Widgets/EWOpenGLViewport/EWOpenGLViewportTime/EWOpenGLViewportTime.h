#pragma once

#include <QTimer>

#include "IEObject.h"
#include "DeltaTime.h"

class EWOpenGLViewport;

class EWOpenGLViewportTime : public IEObject
{
    Q_OBJECT

    QTimer* updateTimer;
    QTimer* renderTimer;
    int updateRefresh;
    int renderRefresh;

    DeltaTime dt;

public:
    EWOpenGLViewportTime(const int msUpdate, const int msRender, QObject* parent = nullptr);
    ~EWOpenGLViewportTime() {}

    void startup(EWOpenGLViewport* viewport);
    void shutdown();

    void startUpdateTimer();
    void startRenderTimer();

    void stopUpdateTimer();
    void stopRenderTimer();

    float processDeltaTime() { return dt.processDeltaTime(); }
    float getDeltaTime() const { return dt.getDeltaTime(); }
    float getFPS() const { return dt.getFPS(); }

private:
    void setupUpdateTimer(EWOpenGLViewport* viewport);
    void setupRenderTimer(EWOpenGLViewport* viewport);
};
