#include "GameStartEvent.h"

GameStartEvent::GameStartEvent(IETime* time_, IEInput* input_, IEScene* scene_) :
    time(time_), input(input_), scene(scene_)
{

}

GameStartEvent::~GameStartEvent()
{

}
