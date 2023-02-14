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
    applicationTitle("Iguana Eye"),
    windowTitle(applicationTitle),
    savePath("")
{
    ui->setupUi(this);

    setupGame();
    setupEditor();
}

ApplicationWindow::~ApplicationWindow()
{
    delete ui;
}

void ApplicationWindow::addTextToTitle(const QString text)
{
    windowTitle = (text.isEmpty()) ? applicationTitle : applicationTitle + " - " + text;
    this->setWindowTitle(windowTitle);
}

void ApplicationWindow::setModifiedStatus(const bool isModified)
{
    auto lastIndex = windowTitle.length() - 1;

    if(isModified)
    {
        if(windowTitle[lastIndex] != '*')
            windowTitle.append("*");
    }
    else
    {
        if(windowTitle[lastIndex] == '*')
            windowTitle = windowTitle.mid(0, lastIndex);
    }

    this->setWindowTitle(windowTitle);
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
    AppStartEvent startEvent(this, editor, game);
    editor->startup(startEvent);
    #endif
}

void ApplicationWindow::newFile()
{
    game->shutdown();
    game->init();
    game->startup();

    #ifdef EDITOR_ENABLED
    AppStartEvent startEvent(this, editor, game);
    editor->shutdown();
    editor->init();
    editor->startup(startEvent);
    #endif
}

bool ApplicationWindow::saveToFile(const QString& path)
{
    return IESerialize::write<IEGame>(path, game);
}

bool ApplicationWindow::openFromFile(const QString& path)
{
    game->shutdown();
    game->init();
    bool success = IESerialize::read<IEGame>(path, game);
    game->startup();

    #ifdef EDITOR_ENABLED
    AppStartEvent startEvent(this, editor, game);
    editor->shutdown();
    editor->init();
    editor->startup(startEvent);
    #endif

    return success;
}

void ApplicationWindow::setupGame()
{
    game = new IEGame(this);
    game->init();
    connect(game, &IEGame::initialized, this, &ApplicationWindow::startup);

    this->setCentralWidget(game);
}

void ApplicationWindow::setupEditor()
{
    #ifdef EDITOR_ENABLED
    editor = new Editor(this);
    editor->init();
    #endif
}
