#include "EWindowManager.h"
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

void EWindowManager::startup()
{
    setupOptionsWindow();
    setupGlslEditorWindow();
    setupFileExplorerWindow();
    setupMessageLogWindow();
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

EWindow* EWindowManager::value(const QString& title) const
{
    if(!doesExist(title))
        return nullptr;

    return &(*windowCollection[title]);
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

void EWindowManager::setupOptionsWindow()
{
    auto& application = ApplicationWindow::instance();

    auto* optionsWindow = new EApplicationOptionsWindow(&application);
    optionsWindow->startup();

    this->appendWindow(optionsWindow->getPermTitle(), optionsWindow);

    application.addDockWidget(Qt::LeftDockWidgetArea, optionsWindow);
}

void EWindowManager::setupGlslEditorWindow()
{
    auto& applicationWindow = ApplicationWindow::instance();

    auto* glslEditorWindow = new EGlslEditorWindow(&applicationWindow);
    glslEditorWindow->startup();

    this->appendWindow(glslEditorWindow->getPermTitle(), glslEditorWindow);

    applicationWindow.addDockWidget(Qt::LeftDockWidgetArea, glslEditorWindow);
}

void EWindowManager::setupFileExplorerWindow()
{
    auto& applicationWindow = ApplicationWindow::instance();

    auto* fileExpWindow = new EFileExplorerWindow(&applicationWindow);
    fileExpWindow->startup();

    this->appendWindow(fileExpWindow->getPermTitle(), fileExpWindow);

    applicationWindow.addDockWidget(Qt::BottomDockWidgetArea, fileExpWindow);

}

void EWindowManager::setupMessageLogWindow()
{
    auto& applicationWindow = ApplicationWindow::instance();

    auto* messageLogWindow = new EMessageLogWindow(&applicationWindow);
    messageLogWindow->startup();

    this->appendWindow(messageLogWindow->getPermTitle(), messageLogWindow);

    applicationWindow.addDockWidget(Qt::BottomDockWidgetArea, messageLogWindow);
}
