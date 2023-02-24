#pragma once

class ApplicationWindow;
class Editor;
class IEGame;

class AppStartEvent
{
    // Does not own these pointers
    ApplicationWindow* appWindow;
    const Editor* editor;
    IEGame* game;

public:
    AppStartEvent(ApplicationWindow* appWindow, Editor* editor_, IEGame* game_);
    ~AppStartEvent();

    ApplicationWindow* getAppWindow() const;
    const Editor* getEditor() const;
    IEGame* getGame() const;
};

