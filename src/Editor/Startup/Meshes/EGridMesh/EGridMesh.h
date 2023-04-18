#pragma once

#include "IEMesh.h"

class EGridMesh : public IEMesh
{

public:
    EGridMesh(QObject* parent = nullptr);
    ~EGridMesh();
};

