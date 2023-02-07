#pragma once

#include "IETime.h"
#include "IEInput.h"
#include "IEScene.h"

class GameStartEvent
{
    // Does not own these
    IETime* time;
    IEInput* input;
    IEScene* scene;

public:
    GameStartEvent(IETime* time_, IEInput* input_, IEScene* scene_);
    ~GameStartEvent();

    IETime* getTime() const { return time; }
    IEInput* getInput() const { return input; }
    IEScene* getScene() const { return scene; }
};

