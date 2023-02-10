#include "GameStartEvent.h"
#include "IETime.h"
#include "IEInput.h"
#include "IEScene.h"

GameStartEvent::GameStartEvent(IETime* time_, IEInput* input_, IEScene* scene_) :
    time(time_), input(input_), scene(scene_)
{

}

GameStartEvent::~GameStartEvent()
{

}

const IETime* GameStartEvent::getTime() const
{
    return time;
}

const IEInput* GameStartEvent::getInput() const
{
    return input;
}

const IEScene* GameStartEvent::getScene() const
{
    return scene;
}
