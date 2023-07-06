#pragma once

#include <QElapsedTimer>

#define MAX_TICKS 100

class DeltaTime
{
    QElapsedTimer timeElapsed;
    int prevTime;
    int currTime;

    int tickIndex;
    int tickSum;
    int tickArr[MAX_TICKS];

    float dt;

public:
    DeltaTime();
    ~DeltaTime();

    float processDeltaTime();

    float getDeltaTime() const { return dt; }
    float getFPS() const { return (1.0f / dt); }

private:
    float calcDeltaTime(const int newTick);
};

