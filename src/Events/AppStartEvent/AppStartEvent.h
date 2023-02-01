#pragma once

#include "ApplicationWindow.h"
#include "Editor.h"
#include "Game.h"

class AppStartEvent
{
    // Does not own these pointers
    ApplicationWindow* myAppWindow;
    Editor* myEditor;
    Game* myGame;

public:
    AppStartEvent(ApplicationWindow* appWindow, Editor* editor_, Game* game_);
    ~AppStartEvent();

    ApplicationWindow* applicationWindow() const;
    Editor* editor() const;
    Game* game() const;
};

