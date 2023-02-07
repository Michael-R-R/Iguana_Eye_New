#pragma once

#include "ApplicationWindow.h"
#include "Editor.h"
#include "Game.h"

class AppStartEvent
{
    // Does not own these pointers
    ApplicationWindow* appWindow;
    Editor* editor;
    Game* game;

public:
    AppStartEvent(ApplicationWindow* appWindow, Editor* editor_, Game* game_);
    ~AppStartEvent();

    ApplicationWindow* getApplicationWindow() const { return appWindow; }
    Editor* getEditor() const { return editor; }
    Game* getGame() const { return game; }
};

