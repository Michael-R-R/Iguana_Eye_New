#include "ApplicationWindow.h"
#include "ui_ApplicationWindow.h"
#include "AppStartEvent.h"
#include "Editor.h"
#include "IEGame.h"
#include "IEGamePlayState.h"
#include "IEGameStopState.h"
#include "IESerialize.h"

ApplicationWindow::ApplicationWindow(QWidget *parent) :
    QMainWindow(parent),
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

void ApplicationWindow::startup()
{
    game = QSharedPointer<IEGame>::create(this);
    connect(&(*game), &IEGame::initialized, this, &ApplicationWindow::initalize);
    this->setCentralWidget(&(*game));
}

void ApplicationWindow::shutdown()
{
    clearActions();
    editor->shutdown();
    editor = nullptr;

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
    game->changeState(QSharedPointer<IEGameStopState>::create(*game));

    editor = QSharedPointer<Editor>::create(this);
    editor->startup(AppStartEvent(this, *editor, *game));
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
    appFileHandler.handleFileNew();
}

void ApplicationWindow::saveToFile()
{
    appFileHandler.handleFileSaved();
}

void ApplicationWindow::saveAsToFile(const QString& path)
{
    appFileHandler.handleFileSavedAs(path);
}

void ApplicationWindow::openFromFile(const QString& path)
{
    appFileHandler.handleFileOpened(path);
}

QDataStream& ApplicationWindow::serialize(QDataStream& out, const Serializable& obj) const
{
    const ApplicationWindow& app = static_cast<const ApplicationWindow&>(obj);

    out << *app.game;

    return out;
}

QDataStream& ApplicationWindow::deserialize(QDataStream& in, Serializable& obj)
{
    ApplicationWindow& app = static_cast<ApplicationWindow&>(obj);
    app.clearActions();

    in >> *app.game;

    app.editor = QSharedPointer<Editor>::create(this);
    app.editor->startup(AppStartEvent(this, *app.editor, *app.game));

    return in;
}
