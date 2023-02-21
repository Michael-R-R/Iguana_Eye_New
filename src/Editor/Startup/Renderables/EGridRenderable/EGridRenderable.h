#pragma once

#include "IERenderable.h"

class IEMeshManager;
class IEMaterialManager;
class IEShaderManager;

class EGridRenderable : public IERenderable
{

public:
    EGridRenderable(const unsigned long long id);
    ~EGridRenderable() {}

    void setup(IEMeshManager* meshManager,
               IEMaterialManager* materialManager,
               IEShaderManager* shaderManager);
};

