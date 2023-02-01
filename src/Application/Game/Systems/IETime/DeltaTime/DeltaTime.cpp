#include "DeltaTime.h"

DeltaTime::DeltaTime() :
    timeElapsed(),
    prevTime(0), currTime(0),
    tickIndex(0), tickSum(0), tickArr(),
    dt(0.0f)
{
    timeElapsed.start();
}

DeltaTime::~DeltaTime()
{

}

float DeltaTime::processDeltaTime()
{
    prevTime = currTime;
    currTime = timeElapsed.elapsed();
    dt = calcDeltaTime(currTime - prevTime);

    return dt;
}

float DeltaTime::calcDeltaTime(const int newTick)
{
    tickSum -= tickArr[tickIndex];
    tickSum += newTick;

    tickArr[tickIndex] = newTick;
    tickIndex = ++tickIndex % MAX_TICKS;

    float average = (float)tickSum / (float)MAX_TICKS;

    return (0.001f * average);
}
