#include "ApplicationWindow.h"
#include "ui_ApplicationWindow.h"
#include "Editor.h"
#include "IEGame.h"
#include "IEGameStopState.h"

ApplicationWindow& ApplicationWindow::instance()
{
    static ApplicationWindow mInstance;
    return mInstance;
}

ApplicationWindow::ApplicationWindow() :
    QMainWindow(),
    ui(new Ui::ApplicationWindow),
    appFileHandler(this),
    game(nullptr),
    editor(nullptr),
    permenentTitle("Iguana Eye"),
    tempTitle(permenentTitle)
{
    ui->setupUi(this);
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

void ApplicationWindow::startup()
{
    game = new IEGame(this);
    connect(game, &IEGame::initialized, this, &ApplicationWindow::initalize);
    this->setCentralWidget(game);
}

void ApplicationWindow::initalize()
{
    disconnect(game, &IEGame::initialized, this, &ApplicationWindow::initalize);
    game->startUp();
    game->changeState(new IEGameStopState(game));

    editor = new Editor(this);
    editor->startup();
}

void ApplicationWindow::shutdown()
{
    clearActions();
    editor->shutdown();
    delete editor;
    editor = nullptr;

    game->shutdown();
    delete game;
    game = nullptr;
}

void ApplicationWindow::onSerialize() const
{
    game->onSerialize();
}

void ApplicationWindow::onDeserialize() const
{
    game->onDeserialize();
}

void ApplicationWindow::newFile()
{
    appFileHandler.handleNewFile();
}

void ApplicationWindow::saveFile()
{
    appFileHandler.handleSaveFile();
}

void ApplicationWindow::saveAsFile(const QString& path)
{
    appFileHandler.handleSaveAsFile(path);
}

void ApplicationWindow::openFile(const QString& path)
{
    appFileHandler.handleOpenFile(path);
}

void ApplicationWindow::clearActions()
{
    auto actionList = this->actions();
    for(auto i : actionList)
    {
        delete i;
        i = nullptr;
    }

    this->addActions(QList<QAction*>());
}

QDataStream& ApplicationWindow::serialize(QDataStream& out, const Serializable& obj) const
{
    const ApplicationWindow& app = static_cast<const ApplicationWindow&>(obj);

    app.onSerialize();

    out << *app.game;

    return out;
}

QDataStream& ApplicationWindow::deserialize(QDataStream& in, Serializable& obj)
{
    ApplicationWindow& app = static_cast<ApplicationWindow&>(obj);

    app.onDeserialize();

    in >> *app.game;

    app.clearActions();
    app.editor->shutdown();
    delete app.editor;
    app.editor = new Editor(&app);
    app.editor->startup();

    return in;
}
