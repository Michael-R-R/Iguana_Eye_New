#pragma once

#include <QObject>

#include "MainMenuBar.h"
#include "StatusBar.h"
#include "EWindowManager.h"

class EGUI : public QObject
{
    MainMenuBar* mainMenuBar;
    StatusBar* statusBar;
    EWindowManager* windowManager;

public:
    EGUI(QObject* parent = nullptr);
    ~EGUI();

    void startup();

    MainMenuBar* getMainMenuBar() const { return mainMenuBar; }
    StatusBar* getStatusBar() const { return statusBar; }
    EWindowManager* getWindowManager() const { return windowManager; }

public slots:
    void toggleUi(bool val);

private:
    void setupMainMenuBar();
    void setupStatusBar();
    void setupWindowManager();
};

