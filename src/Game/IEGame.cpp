#include "IEGame.h"
#include "IEGameState.h"
#include "ApplicationProperties.h"
#include "GameStartEvent.h"
#include "RenderEngineStartEvent.h"
#include "IETime.h"
#include "IEInput.h"
#include "IEScriptEngine.h"
#include "IEPhysicsEngine.h"
#include "IERenderEngine.h"
#include "IEScene.h"
#include "IEECS.h"
#include "IEECSCameraSystem.h"

IEGame::IEGame(QWidget* parent) :
    QOpenGLWidget(parent),
    format(std::make_unique<QSurfaceFormat>()),
    glFunc(nullptr), glExtraFunc(nullptr),
    time(std::make_unique<IETime>(16, 16)),
    input(std::make_unique<IEInput>(this)),
    scriptEngine(std::make_unique<IEScriptEngine>()),
    physicsEngine(std::make_unique<IEPhysicsEngine>()),
    renderEngine(std::make_unique<IERenderEngine>()),
    scene(std::make_unique<IEScene>()),
    state(nullptr)
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
    ApplicationProperties::viewportDimensions = QVector2D(w, h);

    glFunc->glViewport(0, 0, w, h);

    if(state)
        state->onResize((float)w, (float)h);
}

void IEGame::startup()
{
    this->makeCurrent();

    GameStartEvent gameStartEvent(this);
    RenderEngineStartEvent renderStartEvent(*scene);

    scriptEngine->startup(gameStartEvent);
    physicsEngine->startup(gameStartEvent);
    scene->startup(gameStartEvent);
    renderEngine->startup(renderStartEvent);
    time->startup(*this);

    this->setFocus();
}

void IEGame::shutdown()
{
    this->makeCurrent();

    time->shutdown();
    renderEngine->shutdown();
    scene->shutdown();
    physicsEngine->shutdown();
    scriptEngine->shutdown();
}

void IEGame::setState(std::unique_ptr<IEGameState> val)
{
    if(!val)
        return;

    if(state)
    {
        state->exit(*this);
        state = std::move(val);
        state->enter(*this);
    }
    else
    {
        state = std::move(val);
        state->enter(*this);
    }
}

void IEGame::onUpdateFrame()
{
    state->onUpdateFrame();
}

void IEGame::onRenderFrame()
{
    state->onRenderFrame();
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
