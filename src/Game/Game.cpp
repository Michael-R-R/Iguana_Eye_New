#include "Game.h"
#include "GameStartEvent.h"

Game::Game(QWidget* parent) :
    QOpenGLWidget(parent),
    format(new QSurfaceFormat()),
    glFunc(nullptr), glExtraFunc(nullptr),
    time(nullptr), input(nullptr),
    renderEngine(nullptr), scene(nullptr)
{
    format->setVersion(4, 3);
    format->setProfile(QSurfaceFormat::CoreProfile);
    format->setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format->setSwapInterval(1);
    format->setSamples(16);
    this->setFormat(*format); // must be set before window is shown
}

Game::~Game()
{

}

void Game::init()
{
    time = new IETime(8, 16, this);
    input = new IEInput(this, this);
    renderEngine = new IERenderEngine(this);
    scene = new IEScene(this);
}

void Game::startup()
{
    this->makeCurrent();

    GameStartEvent event(time, input, scene);

    scene->startup(event);
    renderEngine->startup(event);
    time->startup(this);

    this->setFocus();
}

void Game::shutdown()
{
    this->makeCurrent();

    time->shutdown();
    renderEngine->shutdown();
    scene->shutdown();

    delete time;
    delete input;
    delete renderEngine;
    delete scene;
}

void Game::onUpdateFrame()
{

}

void Game::onRenderFrame()
{
    glExtraFunc->glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glExtraFunc->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderEngine->onRenderFrame();

    time->processDeltaTime();
}

void Game::initializeGL()
{
    glFunc = QOpenGLContext::currentContext()->functions();
    glExtraFunc = QOpenGLContext::currentContext()->extraFunctions();

    glFunc->initializeOpenGLFunctions();
    glExtraFunc->initializeOpenGLFunctions();

    glExtraFunc->glEnable(GL_MULTISAMPLE);
    glExtraFunc->glEnable(GL_DEPTH_TEST);

    emit initialized();
}

void Game::paintGL()
{
    onRenderFrame();
}

void Game::resizeGL(int w, int h)
{
    glFunc->glViewport(0, 0, w, h);
}
