#include "EditorWindowManager.h"
#include "AppStartEvent.h"
#include "AppOptionsWindow.h"

EditorWindowManager::EditorWindowManager(QObject* parent) :
    QObject(parent),
    windowCollection()
{

}

EditorWindowManager::~EditorWindowManager()
{
    clear();
}

void EditorWindowManager::setup(const AppStartEvent& event)
{
    setupOptionsWindow(event);
}

void EditorWindowManager::clear()
{
    QMapIterator<QString, Window*> it(windowCollection);
    while(it.hasNext())
    {
        it.next();

        auto temp = it.value();
        windowCollection[it.key()] = nullptr;
        delete temp;
    }
}

void EditorWindowManager::showAll()
{
    foreach(auto item, windowCollection.values())
    {
        if(item->getIsActive()) { item->show(); }
    }
}

void EditorWindowManager::hideAll()
{
    foreach(auto item, windowCollection.values())
    {
        if(item->getIsActive()) { item->hide(); }
    }
}

bool EditorWindowManager::appendWindow(const QString title, Window* window)
{
    if(doesExist(title)) { return false; }
    windowCollection[title] = window;

    return true;
}

bool EditorWindowManager::removeWindow(const QString& title)
{
    if(!doesExist(title)) { return false; }
    auto temp = windowCollection[title];
    windowCollection.remove(title);
    delete temp;

    return true;
}

bool EditorWindowManager::doesExist(const QString& title) const
{
    return (windowCollection.find(title) != windowCollection.end());
}

Window* EditorWindowManager::getWindow(const QString& title) const
{
    if(!doesExist(title)) { return nullptr; }
    return windowCollection[title];
}

void EditorWindowManager::setupOptionsWindow(const AppStartEvent& event)
{
    auto applicationWindow = event.applicationWindow();

    auto optionsWindow = new AppOptionsWindow(applicationWindow);
    optionsWindow->setup(event);

    this->appendWindow("Options", optionsWindow);
    applicationWindow->addDockWidget(Qt::LeftDockWidgetArea, optionsWindow);
}
