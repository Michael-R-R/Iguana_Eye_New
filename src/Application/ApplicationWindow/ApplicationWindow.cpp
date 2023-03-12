#include "ApplicationWindow.h"
#include "ui_ApplicationWindow.h"
#include "IESerialize.h"
#include "IEGame.h"

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

    initEditor();
    initGame();
}

ApplicationWindow::~ApplicationWindow()
{
    delete ui;
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

void ApplicationWindow::shutdown()
{
    #ifdef EDITOR_ENABLED
    editor->shutdown();
    #endif

    game->shutdown();
}

void ApplicationWindow::startup()
{
    game->startup();

    #ifdef EDITOR_ENABLED
    AppStartEvent startEvent(this, *editor, *game);
    editor->startup(startEvent);
    #endif

    disconnect(&(*game), &IEGame::initialized, this, &ApplicationWindow::startup);
}

void ApplicationWindow::initGame()
{
    game = std::make_unique<IEGame>(this);
    game->init();
    connect(&(*game), &IEGame::initialized, this, &ApplicationWindow::startup);

    this->setCentralWidget(&(*game));
}

void ApplicationWindow::initEditor()
{
    #ifdef EDITOR_ENABLED
    clearActions();
    editor = std::make_unique<Editor>(this);
    editor->init();
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
    #ifdef EDITOR_ENABLED
    editor = nullptr;
    initEditor();
    #endif

    game = nullptr;
    initGame();
}

bool ApplicationWindow::saveToFile(const QString& path)
{
    return IESerialize::write<IEGame>(path, &(*game));
}

bool ApplicationWindow::openFromFile(const QString& path)
{
    newFile();

    return IESerialize::read<IEGame>(path, &(*game));
}
