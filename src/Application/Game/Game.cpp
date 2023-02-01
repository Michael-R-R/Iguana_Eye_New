#include "Game.h"

Game::Game(QWidget* parent) :
    QOpenGLWidget(parent),
    format(new QSurfaceFormat()),
    glFunc(nullptr), glExtraFunc(nullptr),
    time(new IETime(8, 16, this)),
    input(new IEInput(this, this))
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
    time->setupUpdateTimer(this);
    time->setupRenderTimer(this);
    time->startUpdateTimer();
    time->startRenderTimer();
}

void Game::shutdown()
{

}

void Game::onUpdateFrame()
{
    if(input->isPressed("Forward"))
    {
        qDebug() << "W pressed";
    }
    if(input->isPressed("Backward"))
    {
        qDebug() << "S pressed";
    }
    if(input->isPressed("Left"))
    {
        qDebug() << "A pressed";
    }
    if(input->isPressed("Right"))
    {
        qDebug() << "D pressed";
    }
}

void Game::onRenderFrame()
{
    this->makeCurrent();
    this->update();

    glFunc->glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glFunc->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    qDebug() << time->processDeltaTime();
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
