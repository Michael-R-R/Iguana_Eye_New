#include "RenderEngineStartEvent.h"
#include "IEScene.h"

RenderEngineStartEvent::RenderEngineStartEvent(IEScene* scene_) :
    scene(scene_)
{

}

RenderEngineStartEvent::~RenderEngineStartEvent()
{
    scene = nullptr;
}

const IEScene* RenderEngineStartEvent::getScene() const
{
    return scene;
}
