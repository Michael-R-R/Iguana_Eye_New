#include "EWindowManager.h"
#include "AppStartEvent.h"
#include "ApplicationWindow.h"
#include "EApplicationOptionsWindow.h"
#include "EGlslEditorWindow.h"
#include "EFileExplorerWindow.h"
#include "EMessageLogWindow.h"

EWindowManager::EWindowManager(QObject* parent) :
    QObject(parent),
    windowCollection()
{

}

EWindowManager::~EWindowManager()
{
    clear();
}

void EWindowManager::startup(const AppStartEvent& event)
{
    setupOptionsWindow(event);
    setupGlslEditorWindow(event);
    setupFileExplorerWindow(event);
    setupMessageLogWindow(event);
}

void EWindowManager::showAll()
{
    foreach(auto item, windowCollection.values())
    {
        if(item->getIsActive()) { item->show(); }
    }
}

void EWindowManager::hideAll()
{
    foreach(auto item, windowCollection.values())
    {
        if(item->getIsActive()) { item->hide(); }
    }
}

bool EWindowManager::appendWindow(const QString title, EWindow* window)
{
    if(doesExist(title)) { return false; }
    windowCollection[title] = window;

    return true;
}

bool EWindowManager::removeWindow(const QString& title)
{
    if(!doesExist(title)) { return false; }
    auto temp = windowCollection[title];
    windowCollection.remove(title);
    delete temp;

    return true;
}

EWindow* EWindowManager::value(const QString& title) const
{
    if(!doesExist(title)) { return nullptr; }
    return windowCollection[title];
}

bool EWindowManager::doesExist(const QString& title) const
{
    return (windowCollection.find(title) != windowCollection.end());
}

void EWindowManager::clear()
{
    QMapIterator<QString, EWindow*> it(windowCollection);
    while(it.hasNext())
    {
        it.next();

        auto temp = it.value();
        windowCollection[it.key()] = nullptr;
        delete temp;
    }
}

void EWindowManager::setupOptionsWindow(const AppStartEvent& event)
{
    auto* applicationWindow = event.getAppWindow();

    auto* optionsWindow = new EApplicationOptionsWindow(applicationWindow);
    optionsWindow->startup(event);

    this->appendWindow(optionsWindow->getPermTitle(), optionsWindow);

    applicationWindow->addDockWidget(Qt::LeftDockWidgetArea, optionsWindow);
}

void EWindowManager::setupGlslEditorWindow(const AppStartEvent& event)
{
    auto* applicationWindow = event.getAppWindow();

    auto* glslEditorWindow = new EGlslEditorWindow(applicationWindow);
    glslEditorWindow->startup(event);

    this->appendWindow(glslEditorWindow->getPermTitle(), glslEditorWindow);

    applicationWindow->addDockWidget(Qt::LeftDockWidgetArea, glslEditorWindow);
}

void EWindowManager::setupFileExplorerWindow(const AppStartEvent& event)
{
    auto* applicationWindow = event.getAppWindow();

    auto* fileExpWindow = new EFileExplorerWindow(applicationWindow);
    fileExpWindow->startup(event);

    this->appendWindow(fileExpWindow->getPermTitle(), fileExpWindow);

    applicationWindow->addDockWidget(Qt::BottomDockWidgetArea, fileExpWindow);

}

void EWindowManager::setupMessageLogWindow(const AppStartEvent& event)
{
    auto applicationWindow = event.getAppWindow();

    auto* messageLogWindow = new EMessageLogWindow(applicationWindow);
    messageLogWindow->startup(event);

    this->appendWindow(messageLogWindow->getPermTitle(), messageLogWindow);

    applicationWindow->addDockWidget(Qt::BottomDockWidgetArea, messageLogWindow);
}
