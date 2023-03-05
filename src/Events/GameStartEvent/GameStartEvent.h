#pragma once

class IETime;
class IEInput;
class IEScene;

class GameStartEvent
{
    // Does not own these pointers
    IETime* time;
    IEInput* input;
    IEScene* scene;

public:
    GameStartEvent(IETime* time_, IEInput* input_, IEScene* scene_);
    ~GameStartEvent();

    IETime* getTime() const;
    IEInput* getInput() const;
    IEScene* getScene() const;
};

