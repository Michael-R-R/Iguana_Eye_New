#pragma once

#include "IEMaterial.h"

class EDefaultMaterial : public IEMaterial
{

public:
    EDefaultMaterial(const QString& path);
    ~EDefaultMaterial() {}

};

