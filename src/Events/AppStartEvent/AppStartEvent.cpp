#include "AppStartEvent.h"

AppStartEvent::AppStartEvent(ApplicationWindow* appWindow, Editor* editor_, Game* game_) :
    myAppWindow(appWindow), myEditor(editor_), myGame(game_)
{

}

AppStartEvent::~AppStartEvent()
{

}

ApplicationWindow* AppStartEvent::applicationWindow() const
{
    return myAppWindow;
}

Editor* AppStartEvent::editor() const
{
    return myEditor;
}

Game* AppStartEvent::game() const
{
    return myGame;
}
