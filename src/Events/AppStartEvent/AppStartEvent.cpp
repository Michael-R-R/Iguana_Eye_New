#include "AppStartEvent.h"
#include "ApplicationWindow.h"
#include "Editor.h"
#include "IEGame.h"

AppStartEvent::AppStartEvent(ApplicationWindow* appWindow, Editor* editor_, IEGame* game_) :
    appWindow(appWindow), editor(editor_), game(game_)
{

}

AppStartEvent::~AppStartEvent()
{

}

ApplicationWindow* AppStartEvent::getAppWindow() const
{
    return appWindow;
}

const Editor* AppStartEvent::getEditor() const
{
    return editor;
}

const IEGame* AppStartEvent::getGame() const
{
    return game;
}
