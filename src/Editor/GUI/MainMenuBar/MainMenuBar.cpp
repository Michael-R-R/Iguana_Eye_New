#include "MainMenuBar.h"
#include "AppStartEvent.h"
#include "SubMenu.h"
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

bool MainMenuBar::appendSubMenu(const QString& key, std::unique_ptr<SubMenu> value)
{
    if(doesExist(key))
        return false;

    this->addMenu(&(*value));
    menuCollection[key] = std::move(value);

    return true;
}

bool MainMenuBar::removeSubMenu(const QString& key)
{
    if(!doesExist(key))
        return false;

    menuCollection.erase(key);

    return true;
}

bool MainMenuBar::doesExist(const QString& key)
{
    return (menuCollection.find(key) != menuCollection.end());
}

SubMenu* MainMenuBar::getMenu(const QString& key)
{
    if(!doesExist(key))
        return nullptr;

    return &(*menuCollection[key]);
}

QAction* MainMenuBar::getMenuAction(const QString& menuTitle, const QString& actionTitle)
{
    if(!doesExist(menuTitle))
        return nullptr;

    return menuCollection[menuTitle]->getAction(actionTitle);
}

void MainMenuBar::setupFileSubMenu(const AppStartEvent& event)
{
    auto fileMenu = std::make_unique<FileSubMenu>(this);
    fileMenu->setupActions(event);
    appendSubMenu("File", std::move(fileMenu));
}

void MainMenuBar::setupGameSubMenu(const AppStartEvent& event)
{
    auto gameMenu = std::make_unique<GameSubMenu>(this);
    gameMenu->setupActions(event);
    appendSubMenu("Game", std::move(gameMenu));
}

void MainMenuBar::setupWindowSubMenu(const AppStartEvent& event)
{
    auto windowMenu = std::make_unique<WindowSubMenu>(this);
    windowMenu->setupActions(event);
    appendSubMenu("Window", std::move(windowMenu));
}
