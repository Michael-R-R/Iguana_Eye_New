#include "EWindowManager.h"
#include "EWApplicationOptions.h"
#include "AppStartEvent.h"
#include "ApplicationWindow.h"

EWindowManager::EWindowManager(QObject* parent) :
    QObject(parent),
    windowCollection()
{

}

EWindowManager::~EWindowManager()
{
    clear();
}

void EWindowManager::setup(const AppStartEvent& event)
{
    setupOptionsWindow(event);
}

void EWindowManager::clear()
{
    QMapIterator<QString, EWWindow*> it(windowCollection);
    while(it.hasNext())
    {
        it.next();

        auto temp = it.value();
        windowCollection[it.key()] = nullptr;
        delete temp;
    }
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

bool EWindowManager::appendWindow(const QString title, EWWindow* window)
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

bool EWindowManager::doesExist(const QString& title) const
{
    return (windowCollection.find(title) != windowCollection.end());
}

EWWindow* EWindowManager::getWindow(const QString& title) const
{
    if(!doesExist(title)) { return nullptr; }
    return windowCollection[title];
}

void EWindowManager::setupOptionsWindow(const AppStartEvent& event)
{
    auto applicationWindow = event.getAppWindow();

    auto optionsWindow = new EWApplicationOptions(applicationWindow);
    optionsWindow->setup(event);

    this->appendWindow("Options", optionsWindow);
    applicationWindow->addDockWidget(Qt::LeftDockWidgetArea, optionsWindow);
}
