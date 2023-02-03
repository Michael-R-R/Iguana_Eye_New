#include "ApplicationWindow.h"
#include "ui_ApplicationWindow.h"
#include "IESerialize.h"
#include "Game.h"

#ifdef EDITOR_ENABLED
#include "AppStartEvent.h"
#include "Editor.h"
#endif

ApplicationWindow::ApplicationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ApplicationWindow),
    game(new Game(this)), editor(nullptr),
    applicationTitle("Iguana Eye"), windowTitle(applicationTitle),
    savePath("")
{
    ui->setupUi(this);

    this->setCentralWidget(game);
    connect(game, &Game::initialized, this, &ApplicationWindow::startup);

    #ifdef EDITOR_ENABLED
    editor = new Editor(this);
    #endif
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

void ApplicationWindow::displayModifiedStatus(const bool isModified)
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

bool ApplicationWindow::saveToFile(const QString& path)
{
    return IESerialize::write<Game>(path, game);
}

bool ApplicationWindow::loadFromFile(const QString& path)
{
    if(!IESerialize::read<Game>(path, game))
        return false;

    #ifdef EDITOR_ENABLED
    AppStartEvent startEvent(this, editor, game);
    editor->shutdown();
    editor->startup(startEvent);
    #endif

    return true;
}
