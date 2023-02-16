#include "EGUI.h"
#include "AppStartEvent.h"
#include "ApplicationWindow.h"

EGUI::EGUI(QObject* parent) :
    QObject(parent),
    mainMenuBar(new MainMenuBar()),
    statusBar(new StatusBar()),
    windowManager(new EWindowManager(this))
{

}

EGUI::~EGUI()
{

}

void EGUI::startup(const AppStartEvent& event)
{
    setupMainMenuBar(event);
    setupStatusBar(event);
    setupWindowManager(event);
}

void EGUI::showUi(bool val)
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

void EGUI::setupMainMenuBar(const AppStartEvent& event)
{
    mainMenuBar->setupFileSubMenu(event);
    mainMenuBar->setupGameSubMenu(event);

    auto applicationWindow = event.getAppWindow();
    applicationWindow->setMenuBar(mainMenuBar);
}

void EGUI::setupStatusBar(const AppStartEvent& event)
{
    statusBar->setupIEObjectConnections(event);

    auto applicationWindow = event.getAppWindow();
    applicationWindow->setStatusBar(statusBar);
}

void EGUI::setupWindowManager(const AppStartEvent& event)
{
    windowManager->setup(event);
}
