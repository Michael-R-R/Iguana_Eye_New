#include "ApplicationWindow.h"
#include "ui_ApplicationWindow.h"
#include "Game.h"

#ifdef EDITOR_ENABLED
    #include "Editor.h"
    #include "AppStartEvent.h"
#endif

ApplicationWindow::ApplicationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ApplicationWindow),
    game(new Game(this)), editor(nullptr)
{
    connect(game, &Game::initialized, this, &ApplicationWindow::startup);
}

ApplicationWindow::~ApplicationWindow()
{
    delete ui;
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
    ui->setupUi(this);
    setCentralWidget(game);

    game->startup();

    #ifdef EDITOR_ENABLED
        editor = new Editor(this);
        AppStartEvent startEvent(this, editor, game);
        editor->startup(startEvent);
    #endif
}
