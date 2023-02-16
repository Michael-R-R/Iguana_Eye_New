#pragma once

#include "IEMesh.h"

class EGridMesh : public IEMesh
{

public:
    EGridMesh(const unsigned long long id);
    ~EGridMesh() {}

private:
    void setup();
};

