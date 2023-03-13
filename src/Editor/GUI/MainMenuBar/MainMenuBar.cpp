#include "MainMenuBar.h"
#include "AppStartEvent.h"
#include "FileSubMenu.h"
#include "GameSubMenu.h"
#include "WindowSubMenu.h"

MainMenuBar::MainMenuBar(QWidget* parent) :
    QMenuBar(parent),
    menuCollection()
{

}

MainMenuBar::~MainMenuBar()
{

}

void MainMenuBar::startup(const AppStartEvent& event)
{
    setupFileSubMenu(event);
    setupGameSubMenu(event);
    setupWindowSubMenu(event);
}

bool MainMenuBar::appendSubMenu(QString title, SubMenu* menu)
{
    if(doesExist(title)) { return false; }
    menuCollection[title] = menu;
    this->addMenu(menu);

    return true;
}

bool MainMenuBar::removeSubMenu(const QString& title)
{
    if(!doesExist(title)) { return false; }
    auto temp = menuCollection[title];
    menuCollection.remove(title);
    delete temp;

    return true;
}

bool MainMenuBar::doesExist(const QString& title)
{
    return (menuCollection.find(title) != menuCollection.end());
}

SubMenu* MainMenuBar::getMenu(const QString& title)
{
    if(!doesExist(title)) { return nullptr; }
    return menuCollection[title];
}

QAction* MainMenuBar::getMenuAction(const QString& menuTitle, const QString& actionTitle)
{
    if(!doesExist(menuTitle)) { return nullptr; }
    return menuCollection[menuTitle]->getAction(actionTitle);
}

void MainMenuBar::setupFileSubMenu(const AppStartEvent& event)
{
    auto fileMenu = new FileSubMenu(this);
    fileMenu->setupActions(event);
    appendSubMenu("File", fileMenu);
}

void MainMenuBar::setupGameSubMenu(const AppStartEvent& event)
{
    auto gameMenu = new GameSubMenu(this);
    gameMenu->setupActions(event);
    appendSubMenu("Game", gameMenu);
}

void MainMenuBar::setupWindowSubMenu(const AppStartEvent& event)
{
    auto windowMenu = new WindowSubMenu(this);
    windowMenu->setupActions(event);
    appendSubMenu("Window", windowMenu);
}
