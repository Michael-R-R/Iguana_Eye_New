#include "IEGame.h"
#include "ApplicationWindow.h"
#include "GameStartEvent.h"
#include "RenderEngineStartEvent.h"

IEGame::IEGame(QWidget* parent) :
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

IEGame::~IEGame()
{

}

void IEGame::init()
{
    time = new IETime(8, 16, this);
    input = new IEInput(this, this);
    renderEngine = new IERenderEngine(this);
    scene = new IEScene(this);
}

void IEGame::startup(const ApplicationWindow* appWindow)
{
    this->makeCurrent();

    GameStartEvent gameStartEvent(time, input, scene);
    RenderEngineStartEvent renderStartEvent(scene->getMeshManager(), scene->getMaterialManager(),
                                            scene->getShaderManager(), scene->getRenderableManager());

    scene->startup(gameStartEvent);
    renderEngine->startup(renderStartEvent);
    time->startup(appWindow);

    this->setFocus();
}

void IEGame::shutdown()
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

void IEGame::onUpdateFrame()
{
    scene->onUpdateFrame();
}

void IEGame::onRenderFrame()
{
    glExtraFunc->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderEngine->onRenderFrame();

    time->processDeltaTime();
}

void IEGame::initializeGL()
{
    glFunc = QOpenGLContext::currentContext()->functions();
    glExtraFunc = QOpenGLContext::currentContext()->extraFunctions();

    glFunc->initializeOpenGLFunctions();
    glExtraFunc->initializeOpenGLFunctions();

    glExtraFunc->glEnable(GL_MULTISAMPLE);
    glExtraFunc->glEnable(GL_DEPTH_TEST);

    glExtraFunc->glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

    emit initialized();
}

void IEGame::paintGL()
{
    onRenderFrame();
}

void IEGame::resizeGL(int w, int h)
{
    glFunc->glViewport(0, 0, w, h);
}
