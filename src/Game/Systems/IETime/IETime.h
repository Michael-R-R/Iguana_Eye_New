#pragma once

#include <QTimer>
#include <QDataStream>

#include "IEObject.h"
#include "DeltaTime.h"

class ApplicationWindow;

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

    void startup(const ApplicationWindow* application);
    void shutdown();

    void setupUpdateTimer(const ApplicationWindow* application);
    void setupRenderTimer(const ApplicationWindow* application);

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

    friend QDataStream& operator<<(QDataStream& out, const IETime& time)
    {
        out << time.updateRefresh << time.renderRefresh;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IETime& time)
    {
        in >> time.updateRefresh >> time.renderRefresh;
        return in;
    }
};
