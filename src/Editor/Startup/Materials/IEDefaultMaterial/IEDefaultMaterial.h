#pragma once

#include "IEMaterial.h"

class IEDefaultMaterial : public IEMaterial
{

public:
    IEDefaultMaterial(const QString& path);
    ~IEDefaultMaterial() {}

};

