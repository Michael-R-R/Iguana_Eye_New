#include "EGUI.h"
#include "AppStartEvent.h"
#include "ApplicationWindow.h"

EGUI::EGUI(QObject* parent) :
    QObject(parent),
    mainMenuBar(std::make_unique<MainMenuBar>()),
    statusBar(std::make_unique<StatusBar>()),
    windowManager(std::make_unique<EWindowManager>())
{

}

EGUI::~EGUI()
{

}

void EGUI::startup(const AppStartEvent& event)
{
    // *** DO NOT REORDER *** //
    setupWindowManager(event);
    setupStatusBar(event);
    setupMainMenuBar(event);
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

void EGUI::setupMainMenuBar(const AppStartEvent& event)
{
    mainMenuBar->startup(event);

    auto* applicationWindow = event.getAppWindow();
    applicationWindow->setMenuBar(&(*mainMenuBar));
}

void EGUI::setupStatusBar(const AppStartEvent& event)
{
    statusBar->setupIEObjectConnections(event);

    auto applicationWindow = event.getAppWindow();
    applicationWindow->setStatusBar(&(*statusBar));
}

void EGUI::setupWindowManager(const AppStartEvent& event)
{
    windowManager->startup(event);
}
