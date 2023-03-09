#include "IEGame.h"
#include "GameStartEvent.h"
#include "RenderEngineStartEvent.h"

IEGame::IEGame(QWidget* parent) :
    QOpenGLWidget(parent),
    format(new QSurfaceFormat()),
    glFunc(nullptr), glExtraFunc(nullptr),
    time(nullptr), input(nullptr),
    scriptEngine(nullptr), renderEngine(nullptr),
    scene(nullptr),
    viewportWidth(0), viewportHeight(0)
{
    this->setFocusPolicy(Qt::StrongFocus);

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
    time = new IETime(16, 16, this);
    input = new IEInput(this, this);
    scriptEngine = new IEScriptEngine(this);
    renderEngine = new IERenderEngine(this);
    scene = new IEScene(this);
}

void IEGame::startup()
{
    this->makeCurrent();

    GameStartEvent gameStartEvent(time, input, scene);
    RenderEngineStartEvent renderStartEvent(scene);

    scene->startup(gameStartEvent);
    scriptEngine->startup(gameStartEvent);
    renderEngine->startup(renderStartEvent);
    time->startup(this);

    this->setFocus();
}

void IEGame::shutdown()
{
    this->makeCurrent();

    time->shutdown();
    renderEngine->shutdown();
    scriptEngine->shutdown();
    scene->shutdown();

    delete time;
    delete input;
    delete scriptEngine;
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

    glExtraFunc->glEnable(GL_DEPTH_TEST);
    glExtraFunc->glEnable(GL_MULTISAMPLE);
    glExtraFunc->glEnable(GL_BLEND);

    glExtraFunc->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glExtraFunc->glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

    emit initialized();
}

void IEGame::paintGL()
{
    onRenderFrame();
}

void IEGame::resizeGL(int w, int h)
{
    viewportWidth = w;
    viewportHeight = h;

    glFunc->glViewport(0, 0, w, h);
}
