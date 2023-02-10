#pragma once

class ApplicationWindow;
class Editor;
class Game;

class AppStartEvent
{
    // Does not own these pointers
    ApplicationWindow* appWindow;
    Editor* editor;
    Game* game;

public:
    AppStartEvent(ApplicationWindow* appWindow, Editor* editor_, Game* game_);
    ~AppStartEvent();

    ApplicationWindow* getAppWindow() const;
    Editor* getEditor() const;
    Game* getGame() const;
};

