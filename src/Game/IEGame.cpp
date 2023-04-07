#include "IEGame.h"
#include "IEGameState.h"
#include "IETime.h"
#include "IEInput.h"
#include "IEScriptEngine.h"
#include "IEPhysicsEngine.h"
#include "IERenderEngine.h"
#include "IEScene.h"
#include "IEECS.h"
#include "ApplicationProperties.h"

IEGame::IEGame(QWidget* parent) :
    QOpenGLWidget(parent),
    format(),
    glFunc(nullptr),
    glExtraFunc(nullptr),
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
    IETime::instance().processDeltaTime();
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
    IERenderEngine::instance().startup(*this);
    IEPhysicsEngine::instance().startup(*this);
    IEScene::instance().startup(*this);
    IEECS::instance().startup(*this);
    IEInput::instance().startup(*this);
    IEScriptEngine::instance().startup(*this);
    IETime::instance().startup(*this);
}

void IEGame::shutdown()
{
    this->makeCurrent();
    IETime::instance().shutdown(*this);
    IEScriptEngine::instance().shutdown(*this);
    IEInput::instance().shutdown(*this);
    IEECS::instance().shutdown(*this);
    IEScene::instance().shutdown(*this);
    IEPhysicsEngine::instance().shutdown(*this);
    IERenderEngine::instance().shutdown(*this);
}

void IEGame::initalize()
{
    IEECS::instance().initalize(*this);
}

void IEGame::reset()
{
    IEPhysicsEngine::instance().reset(*this);
    IEScriptEngine::instance().reset(*this);
    IEECS::instance().reset(*this);
}

void IEGame::changeState(std::unique_ptr<IEGameState> val)
{
    this->makeCurrent();

    if(state)
        state->exit(*this);
    state = std::move(val);
    state->enter(*this);
}

void IEGame::onUpdateFrame()
{
    state->onUpdateFrame();
}

void IEGame::onRenderFrame()
{
    this->update();
}

QDataStream& IEGame::serialize(QDataStream& out, const Serializable&) const
{
    out << IETime::instance()
        << IEInput::instance()
        << IEScene::instance()
        << IEECS::instance();

    return out;
}

QDataStream& IEGame::deserialize(QDataStream& in, Serializable&)
{
    in >> IETime::instance()
       >> IEInput::instance()
       >> IEScene::instance()
       >> IEECS::instance();

    return in;
}
