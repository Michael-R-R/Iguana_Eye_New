#include "Game.h"

Game::Game(QWidget* parent) :
    QOpenGLWidget(parent),
    format(new QSurfaceFormat()),
    glFunc(nullptr), glExtraFunc(nullptr),
    time(new IETime(8, 16, this)),
    input(new IEInput(this, this)),
    scene(new IEScene(this))
{
    format->setVersion(4, 3);
    format->setProfile(QSurfaceFormat::CoreProfile);
    format->setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format->setSwapInterval(1);
    this->setFormat(*format); // must be set before window is shown
}

Game::~Game()
{

}

void Game::startup()
{
    this->setFocus();
    time->setupUpdateTimer(this);
    time->setupRenderTimer(this);
    time->startUpdateTimer();
    time->startRenderTimer();
}

void Game::shutdown()
{
    time->stopUpdateTimer();
    time->stopRenderTimer();

    delete time;
    delete input;
    delete scene;
}

void Game::onUpdateFrame()
{

}

void Game::onRenderFrame()
{
    this->makeCurrent();
    this->update();

    glFunc->glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glFunc->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    time->processDeltaTime();
}

void Game::initializeGL()
{
    glFunc = QOpenGLContext::currentContext()->functions();
    glExtraFunc = QOpenGLContext::currentContext()->extraFunctions();

    emit initialized();
}

void Game::resizeGL(int w, int h)
{
    glFunc->glViewport(0, 0, w, h);
}

QDataStream& operator<<(QDataStream& out, const Game& game)
{
    out << *game.getIETime() << *game.getIEInput() << *game.getIEScene();

    return out;
}

QDataStream& operator>>(QDataStream& in, Game& game)
{
    game.shutdown();

    IETime* time = new IETime(0, 0, &game);
    IEInput* input = new IEInput(&game, &game);
    IEScene* scene = new IEScene(&game);

    in >> *time >> *input >> *scene;

    game.setIETime(time);
    game.setIEInput(input);
    game.setIEScene(scene);

    game.startup();

    return in;
}

