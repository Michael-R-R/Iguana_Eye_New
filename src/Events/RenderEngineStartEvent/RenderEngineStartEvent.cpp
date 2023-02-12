#include "RenderEngineStartEvent.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"

RenderEngineStartEvent::RenderEngineStartEvent(IEMeshManager* meshManager_, IEMaterialManager* materialManager_,
                                               IEShaderManager* shaderManager_, IERenderableManager* renderableManager_) :
    meshManager(meshManager_), materialManager(materialManager_),
    shaderManager(shaderManager_), renderableManager(renderableManager_)
{

}

const IEMeshManager* RenderEngineStartEvent::getMeshManager() const
{
    return meshManager;
}

const IEMaterialManager* RenderEngineStartEvent::getMaterialManager() const
{
    return materialManager;
}

const IEShaderManager* RenderEngineStartEvent::getShaderManager() const
{
    return shaderManager;
}

const IERenderableManager* RenderEngineStartEvent::getRenderableManager() const
{
    return renderableManager;
}
