#include "GameStartEvent.h"
#include "IEGame.h"
#include "IETime.h"

GameStartEvent::GameStartEvent(IEGame* game_) :
    game(game_)
{

}

GameStartEvent::~GameStartEvent()
{
    game = nullptr;
}

IETime& GameStartEvent::getTime() const
{
    return game->getIETime();
}

IEInput& GameStartEvent::getInput() const
{
    return game->getIEInput();
}

IEScriptEngine& GameStartEvent::getScriptEngine() const
{
    return game->getIEScriptEngine();
}

IERenderEngine& GameStartEvent::getRenderEngine() const
{
    return game->getIERenderEngine();
}

IEScene* GameStartEvent::getScene() const
{
    return game->getIEScene();
}
