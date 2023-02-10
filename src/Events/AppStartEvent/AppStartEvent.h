#pragma once

class ApplicationWindow;
class Editor;
class Game;

class AppStartEvent
{
    // Does not own these pointers
    ApplicationWindow* appWindow;
    const Editor* editor;
    const Game* game;

public:
    AppStartEvent(ApplicationWindow* appWindow, Editor* editor_, Game* game_);
    ~AppStartEvent();

    ApplicationWindow* getAppWindow() const;
    const Editor* getEditor() const;
    const Game* getGame() const;
};

