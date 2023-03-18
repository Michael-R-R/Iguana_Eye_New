#include "IEGame.h"
#include "GameStartEvent.h"
#include "RenderEngineStartEvent.h"
#include "IETime.h"
#include "IEInput.h"
#include "IEScriptEngine.h"
#include "IERenderEngine.h"
#include "IEScene.h"
#include "IEECS.h"
#include "IEECSCameraSystem.h"

// TODO test
#include "IETCreateRenderable.h"

IEGame::IEGame(QWidget* parent) :
    QOpenGLWidget(parent),
    format(std::make_unique<QSurfaceFormat>()),
    glFunc(nullptr), glExtraFunc(nullptr),
    time(std::make_unique<IETime>(16, 16)),
    input(std::make_unique<IEInput>(this)),
    scriptEngine(std::make_unique<IEScriptEngine>()),
    renderEngine(std::make_unique<IERenderEngine>()),
    scene(std::make_unique<IEScene>()),
    viewportWidth(800), viewportHeight(600)
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

    auto& ecs = scene->getECS();
    auto* cameraSystem = ecs.getComponent<IEECSCameraSystem>("Camera");
    cameraSystem->setHasDirtyProj(true);
}

void IEGame::startup()
{
    this->makeCurrent();

    GameStartEvent gameStartEvent(this);
    RenderEngineStartEvent renderStartEvent(*scene);

    scriptEngine->startup(gameStartEvent);
    scene->startup(gameStartEvent);
    renderEngine->startup(renderStartEvent);
    time->startup(*this);

    // TODO test
    IETCreateRenderable test(gameStartEvent);

    this->setFocus();
}

void IEGame::shutdown()
{
    this->makeCurrent();

    time->shutdown();
    renderEngine->shutdown();
    scene->shutdown();
    scriptEngine->shutdown();
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

QDataStream& IEGame::serialize(QDataStream& out, const Serializable& obj) const
{
    const IEGame& game = static_cast<const IEGame&>(obj);

    out << *game.time << *game.input << *game.scene;

    return out;
}

QDataStream& IEGame::deserialize(QDataStream& in, Serializable& obj)
{
    IEGame& game = static_cast<IEGame&>(obj);

    in >> *game.time >> *game.input >> *game.scene;

    return in;
}
