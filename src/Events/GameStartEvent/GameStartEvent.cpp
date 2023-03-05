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
    time = nullptr;
    input = nullptr;
    scene = nullptr;
}

IETime* GameStartEvent::getTime() const
{
    return time;
}

IEInput* GameStartEvent::getInput() const
{
    return input;
}

IEScene* GameStartEvent::getScene() const
{
    return scene;
}
