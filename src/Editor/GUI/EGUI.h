#pragma once

#include <QObject>

#include "MainMenuBar.h"
#include "StatusBar.h"
#include "EWindowManager.h"

class AppStartEvent;

class EGUI : public QObject
{
    std::unique_ptr<MainMenuBar> mainMenuBar;
    StatusBar* statusBar;
    EWindowManager* windowManager;

public:
    EGUI(QObject* parent = nullptr);
    ~EGUI();

    void startup(const AppStartEvent& event);

    MainMenuBar& getMainMenuBar() const { return *mainMenuBar; }
    StatusBar* getStatusBar() const { return statusBar; }
    EWindowManager* getWindowManager() const { return windowManager; }

public slots:
    void toggleUi(bool val);

private:
    void setupMainMenuBar(const AppStartEvent& event);
    void setupStatusBar(const AppStartEvent& event);
    void setupWindowManager(const AppStartEvent& event);
};

