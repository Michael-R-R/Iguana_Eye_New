#pragma once

class IEScene;

class RenderEngineStartEvent
{
    // Does not own these pointers
    const IEScene* scene;

public:
    RenderEngineStartEvent(IEScene* scene_);
    ~RenderEngineStartEvent();

    const IEScene* getScene() const;
};

