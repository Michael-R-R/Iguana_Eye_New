#include "EditorUi.h"
#include "AppStartEvent.h"

EditorUi::EditorUi(QObject* parent) :
    QObject(parent),
    mainMenuBar(new MainMenuBar()),
    statusBar(new StatusBar()),
    windowManager(new EditorWindowManager(this))
{

}

EditorUi::~EditorUi()
{

}

void EditorUi::setup(const AppStartEvent& event)
{
    setupMainMenuBar(event);
    setupStatusBar(event);
    setupWindowManager(event);
}

void EditorUi::showUi(bool val)
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

void EditorUi::setupMainMenuBar(const AppStartEvent& event)
{
    mainMenuBar->setupFileSubMenu(event);
    mainMenuBar->setupGameSubMenu(event);

    auto applicationWindow = event.applicationWindow();
    applicationWindow->setMenuBar(mainMenuBar);
}

void EditorUi::setupStatusBar(const AppStartEvent& event)
{
    statusBar->setupIEObjectConnections(event);

    auto applicationWindow = event.applicationWindow();
    applicationWindow->setStatusBar(statusBar);
}

void EditorUi::setupWindowManager(const AppStartEvent& event)
{
    windowManager->setup(event);
}
