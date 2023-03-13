#include "EWindowManager.h"
#include "AppStartEvent.h"
#include "ApplicationWindow.h"
#include "EApplicationOptionsWindow.h"
#include "EGlslEditorWindow.h"
#include "EFileExplorerWindow.h"

EWindowManager::EWindowManager() :
    windowCollection()
{

}

EWindowManager::~EWindowManager()
{

}

void EWindowManager::startup(const AppStartEvent& event)
{
    setupOptionsWindow(event);
    setupGlslEditorWindow(event);
    setupFileExplorerWindow(event);
}

void EWindowManager::showAll()
{
    for(auto& i : windowCollection)
    {
        if(i.second->getIsActive())
            i.second->show();
    }
}

void EWindowManager::hideAll()
{
    for(auto& i : windowCollection)
    {
        if(i.second->getIsActive())
            i.second->hide();
    }
}

bool EWindowManager::appendWindow(const QString& key, std::unique_ptr<EWindow> value)
{
    if(doesExist(key))
        return false;

    windowCollection[key] = std::move(value);

    return true;
}

bool EWindowManager::removeWindow(const QString& key)
{
    if(!doesExist(key))
        return false;

    windowCollection.erase(key);

    return true;
}

EWindow* EWindowManager::getValue(const QString& key)
{
    if(!doesExist(key))
        return nullptr;

    return &(*windowCollection[key]);
}

bool EWindowManager::doesExist(const QString& key) const
{
    return (windowCollection.find(key) != windowCollection.end());
}

void EWindowManager::clear()
{
    windowCollection.clear();
}

void EWindowManager::setupOptionsWindow(const AppStartEvent& event)
{
    auto applicationWindow = event.getAppWindow();

    auto optionsWindow = std::make_unique<EApplicationOptionsWindow>(applicationWindow);
    optionsWindow->startup(event);

    applicationWindow->addDockWidget(Qt::LeftDockWidgetArea, &(*optionsWindow));

    this->appendWindow("Options", std::move(optionsWindow));
}

void EWindowManager::setupGlslEditorWindow(const AppStartEvent& event)
{
    auto applicationWindow = event.getAppWindow();

    auto glslEditorWindow = std::make_unique<EGlslEditorWindow>(applicationWindow);
    glslEditorWindow->startup(event);

    applicationWindow->addDockWidget(Qt::LeftDockWidgetArea, &(*glslEditorWindow));

    this->appendWindow("GLSL Editor", std::move(glslEditorWindow));
}

void EWindowManager::setupFileExplorerWindow(const AppStartEvent& event)
{
    auto applicationWindow = event.getAppWindow();

    auto fileExpWindow = std::make_unique<EFileExplorerWindow>(applicationWindow);
    fileExpWindow->startup();

    applicationWindow->addDockWidget(Qt::BottomDockWidgetArea, &(*fileExpWindow));

    this->appendWindow("File Explorer", std::move(fileExpWindow));
}
