#include "ApplicationWindow.h"
#include "ui_ApplicationWindow.h"
#include "AppStartEvent.h"
#include "Editor.h"
#include "IEGame.h"
#include "IEGamePlayState.h"
#include "IEGameStopState.h"
#include "IESerialize.h"

ApplicationWindow::ApplicationWindow(bool buildEditor, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ApplicationWindow),
    game(nullptr),
    editor(nullptr),
    permenentTitle("Iguana Eye"),
    tempTitle(permenentTitle),
    savePath(""),
    doBuildEditor(buildEditor)
{
    ui->setupUi(this);
}

ApplicationWindow::~ApplicationWindow()
{
    IEFile::removeAllFiles("./resources/temp/backup/");

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
    if(doBuildEditor)
    {
        clearActions();
        editor->shutdown();
        editor = nullptr;
    }

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
    game->startup();
    game->changeState(std::move(std::make_unique<IEGameStopState>(*game)));

    if(doBuildEditor)
    {
        editor = std::make_unique<Editor>(this);
        editor->startup(AppStartEvent(this, *editor, *game));
    }
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
    game->changeState(std::move(std::make_unique<IEGameStopState>(*game)));
    if(!IESerialize::read<IEGame>(path, &(*game)))
            return false;

    if(doBuildEditor)
    {
        clearActions();
        editor = std::make_unique<Editor>(this);
        editor->startup(AppStartEvent(this, *editor, *game));
    }

    return true;
}
