#include "EGUI.h"
#include "ApplicationWindow.h"

EGUI::EGUI(QWidget* parent) :
    QWidget(parent),
    mainMenuBar(new MainMenuBar(this)),
    statusBar(new StatusBar(this)),
    windowManager(new EWindowManager(this))
{

}

EGUI::~EGUI()
{

}

void EGUI::startup()
{
    // *** DO NOT REORDER *** //
    setupWindowManager();
    setupStatusBar();
    setupMainMenuBar();
}

void EGUI::shutdown()
{

}

void EGUI::toggleUi(bool val)
{
    if(val)
    {
        mainMenuBar->show();
        statusBar->show();
        windowManager->showAll();
    }
    else
    {
        mainMenuBar->hide();
        statusBar->hide();
        windowManager->hideAll();
    }
}

void EGUI::setupMainMenuBar()
{
    mainMenuBar->startup();

    auto& applicationWindow = ApplicationWindow::instance();
    applicationWindow.setMenuBar(mainMenuBar);
}

void EGUI::setupStatusBar()
{
    statusBar->startup();

    auto& applicationWindow = ApplicationWindow::instance();
    applicationWindow.setStatusBar(statusBar);
}

void EGUI::setupWindowManager()
{
    windowManager->startup();
}
