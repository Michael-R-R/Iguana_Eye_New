#pragma once

class IETime;
class IEInput;
class IEScene;

class GameStartEvent
{
    // Does not own these pointers
    const IETime* time;
    const IEInput* input;
    const IEScene* scene;

public:
    GameStartEvent(IETime* time_, IEInput* input_, IEScene* scene_);
    ~GameStartEvent();

    const IETime* getTime() const;
    const IEInput* getInput() const;
    const IEScene* getScene() const;
};

