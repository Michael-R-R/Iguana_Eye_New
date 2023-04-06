#include "ApplicationWindow.h"
#include "ui_ApplicationWindow.h"
#include "IESerialize.h"
#include "IEGame.h"
#include "IEGameStopState.h"

#ifdef EDITOR_ENABLED
#include "AppStartEvent.h"
#include "Editor.h"
#endif

ApplicationWindow::ApplicationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ApplicationWindow),
    game(nullptr),
    editor(nullptr),
    permenentTitle("Iguana Eye"),
    tempTitle(permenentTitle),
    savePath("")
{
    ui->setupUi(this);
}

ApplicationWindow::~ApplicationWindow()
{
    delete ui;
}

void ApplicationWindow::startup()
{
    game = std::make_unique<IEGame>(this);
    connect(&(*game), &IEGame::initialized, this, &ApplicationWindow::initalize);
    this->setCentralWidget(&(*game));
}

void ApplicationWindow::shutdown()
{
    #ifdef EDITOR_ENABLED
    clearActions();
    editor->shutdown();
    editor = nullptr;
    #endif

    game->shutdown();
    game = nullptr;
}

void ApplicationWindow::modifyTitle(const QString& text)
{
    tempTitle = (text.isEmpty()) ? permenentTitle : permenentTitle + " - " + text;
    this->setWindowTitle(tempTitle);
}

void ApplicationWindow::setModified(const bool isModified)
{
    auto lastIndex = tempTitle.length() - 1;

    if(isModified)
    {
        if(tempTitle[lastIndex] != '*')
            tempTitle.append("*");
    }
    else
    {
        if(tempTitle[lastIndex] == '*')
            tempTitle = tempTitle.mid(0, lastIndex);
    }

    this->setWindowTitle(tempTitle);
}

void ApplicationWindow::initalize()
{
    disconnect(&(*game), &IEGame::initialized, this, &ApplicationWindow::initalize);
    game->stop(false);
    game->startup();

    #ifdef EDITOR_ENABLED
    editor = std::make_unique<Editor>(this);
    editor->startup(AppStartEvent(this, *editor, *game));
    #endif
}

void ApplicationWindow::clearActions()
{
    auto actionList = this->actions();
    for(auto item : actionList)
    {
        delete item;
        item = nullptr;
    }
    actionList.clear();
    this->addActions(actionList);
}

void ApplicationWindow::newFile()
{
    this->shutdown();
    this->startup();
}

bool ApplicationWindow::saveToFile(const QString& path)
{
    return IESerialize::write<IEGame>(path, &(*game));
}

bool ApplicationWindow::openFromFile(const QString& path)
{
    game->makeCurrent();
    game->stop(false);
    if(!IESerialize::read<IEGame>(path, &(*game)))
            return false;

    #ifdef EDITOR_ENABLED
    clearActions();
    editor = std::make_unique<Editor>(this);
    editor->startup(AppStartEvent(this, *editor, *game));
    #endif

    return true;
}
