#pragma once

class IEScene;

class RenderEngineStartEvent
{
    const IEScene& scene;

public:
    RenderEngineStartEvent(IEScene& scene_);
    ~RenderEngineStartEvent();

    const IEScene& getScene() const;
};

