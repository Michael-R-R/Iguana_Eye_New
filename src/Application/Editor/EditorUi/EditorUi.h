#pragma once

#include <QObject>

#include "MainMenuBar.h"
#include "StatusBar.h"
#include "EditorWindowManager.h"

class AppStartEvent;

class EditorUi : public QObject
{
    MainMenuBar* mainMenuBar;
    StatusBar* statusBar;
    EditorWindowManager* windowManager;

public:
    EditorUi(QObject* parent = nullptr);
    ~EditorUi();

    void setup(const AppStartEvent& event);

    MainMenuBar* getMainMenuBar() const { return mainMenuBar; }
    StatusBar* getStatusBar() const { return statusBar; }
    EditorWindowManager* getWindowManager() const { return windowManager; }

public slots:
    void showUi(bool val);

private:
    void setupMainMenuBar(const AppStartEvent& event);
    void setupStatusBar(const AppStartEvent& event);
    void setupWindowManager(const AppStartEvent& event);
};

