#include "MainMenuBar.h"
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

void MainMenuBar::startup()
{
    setupFileSubMenu();
    setupGameSubMenu();
    setupWindowSubMenu();
}

void MainMenuBar::shutdown()
{

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

void MainMenuBar::setupFileSubMenu()
{
    auto fileMenu = new FileSubMenu(this);
    fileMenu->startup();
    appendSubMenu("File", fileMenu);
}

void MainMenuBar::setupGameSubMenu()
{
    auto gameMenu = new GameSubMenu(this);
    gameMenu->setupActions();
    appendSubMenu("Game", gameMenu);
}

void MainMenuBar::setupWindowSubMenu()
{
    auto windowMenu = new WindowSubMenu(this);
    windowMenu->setupActions();
    appendSubMenu("Window", windowMenu);
}
