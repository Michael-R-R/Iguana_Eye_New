#include "AppStartEvent.h"

AppStartEvent::AppStartEvent(ApplicationWindow* appWindow, Editor* editor_, Game* game_) :
    appWindow(appWindow), editor(editor_), game(game_)
{

}

AppStartEvent::~AppStartEvent()
{

}
