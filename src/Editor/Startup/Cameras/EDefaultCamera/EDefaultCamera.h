#pragma once

#include "IECamera.h"

class EDefaultCamera : public IECamera
{
public:
    EDefaultCamera(const QString& path, const unsigned long long resourceId);
    ~EDefaultCamera() {}
};

