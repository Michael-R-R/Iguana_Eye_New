#pragma once

#include <QWidget>

#include "MainMenuBar.h"
#include "StatusBar.h"
#include "EWindowManager.h"

class EGUI : public QWidget
{
    MainMenuBar* mainMenuBar;
    StatusBar* statusBar;
    EWindowManager* windowManager;

public:
    EGUI(QWidget* parent = nullptr);
    ~EGUI();

    void startup();
    void shutdown();

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

