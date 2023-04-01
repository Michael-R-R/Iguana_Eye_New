#include "IEGame.h"
#include "IETime.h"
#include "IEInput.h"
#include "IEScriptEngine.h"
#include "IEPhysicsEngine.h"
#include "IERenderEngine.h"
#include "IEScene.h"
#include "IEECS.h"
#include "IEGameState.h"
#include "ApplicationProperties.h"

IEGame::IEGame(QWidget* parent) :
    QOpenGLWidget(parent),
    format(),
    glFunc(nullptr), glExtraFunc(nullptr),
    time(std::make_unique<IETime>(16, 16, *this)),
    input(std::make_unique<IEInput>(this)),
    physicsEngine(std::make_unique<IEPhysicsEngine>()),
    scene(std::make_unique<IEScene>()),
    ecs(std::make_unique<IEECS>(*this)),
    scriptEngine(std::make_unique<IEScriptEngine>(*this)),
    renderEngine(std::make_unique<IERenderEngine>(*scene)),
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
    time->startup();
}

void IEGame::shutdown()
{
    this->makeCurrent();
    time->shutdown();
}

void IEGame::reset()
{
    this->makeCurrent();
    time->shutdown();
    physicsEngine->reset();
    scriptEngine->reset(*this);
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
    this->update();
}

QDataStream& IEGame::serialize(QDataStream& out, const Serializable& obj) const
{
    const IEGame& game = static_cast<const IEGame&>(obj);

    out << *game.time << *game.input << *game.scene << *game.ecs;

    return out;
}

QDataStream& IEGame::deserialize(QDataStream& in, Serializable& obj)
{
    IEGame& game = static_cast<IEGame&>(obj);

    in >> *game.time >> *game.input >> *game.scene >> *game.ecs;

    return in;
}
