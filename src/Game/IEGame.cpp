#include "IEGame.h"
#include "ApplicationProperties.h"
#include "IERenderEngine.h"
#include "IEPhysicsEngine.h"
#include "IEScene.h"
#include "IEECS.h"
#include "IEInput.h"
#include "IEScriptEngine.h"
#include "IETime.h"
#include "IEGameState.h"

IEGame::IEGame(QWidget* parent) :
    QOpenGLWidget(parent),
    format(),
    glFunc(nullptr),
    glExtraFunc(nullptr),
    renderEngine(QSharedPointer<IERenderEngine>::create()),
    physicsEngine(QSharedPointer<IEPhysicsEngine>::create()),
    scene(QSharedPointer<IEScene>::create()),
    ecs(QSharedPointer<IEECS>::create()),
    input(QSharedPointer<IEInput>::create()),
    scriptEngine(QSharedPointer<IEScriptEngine>::create()),
    time(QSharedPointer<IETime>::create()),
    state(nullptr)
{
    this->setFocusPolicy(Qt::StrongFocus);

    format.setVersion(4, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format.setSwapInterval(1);
    format.setSamples(16);
    this->setFormat(format); // must be set before window is shown
    this->setUpdateBehavior(UpdateBehavior::PartialUpdate);
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
    state->onRenderFrame();
    time->processDeltaTime();
}

void IEGame::resizeGL(int w, int h)
{
    glFunc->glViewport(0, 0, w, h);

    ApplicationProperties::viewportDimensions = QVector2D(w, h);

    if(state) { state->onResize((float)w, (float)h); }
}

void IEGame::startup()
{
    this->makeCurrent();
    renderEngine->startup(*this);
    physicsEngine->startup(*this);
    scene->startup(*this);
    ecs->startup(*this);
    input->startup(*this);
    scriptEngine->startup(*this);
    time->startup(*this);
}

void IEGame::shutdown()
{
    this->makeCurrent();
    time->shutdown(*this);
    scriptEngine->shutdown(*this);
    input->shutdown(*this);
    ecs->shutdown(*this);
    scene->shutdown(*this);
    physicsEngine->shutdown(*this);
    renderEngine->shutdown(*this);
}

void IEGame::initalize()
{
    ecs->initalize(*this);
}

void IEGame::reset()
{
    physicsEngine->reset(*this);
    scriptEngine->reset(*this);
    ecs->reset(*this);
}

void IEGame::changeState(QSharedPointer<IEGameState> val)
{
    this->makeCurrent();

    if(state)
        state->exit(*this);
    state = val;
    state->enter(*this);

    emit stateChanged(val);
}

void IEGame::onUpdateFrame()
{
    state->onUpdateFrame();
}

void IEGame::onRenderFrame()
{
    this->update();
}

QDataStream& IEGame::serialize(QDataStream& out, const Serializable& obj) const
{
    const IEGame& game = static_cast<const IEGame&>(obj);

    out << *game.time
        << *game.input
        << *game.scene
        << *game.ecs;

    return out;
}

QDataStream& IEGame::deserialize(QDataStream& in, Serializable& obj)
{
    IEGame& game = static_cast<IEGame&>(obj);
    game.makeCurrent();

    in >> *game.time
        >> *game.input
        >> *game.scene
        >> *game.ecs;

    return in;
}
