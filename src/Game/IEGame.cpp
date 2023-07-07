#include "IEGame.h"
#include "ApplicationProperties.h"
#include "IERenderEngine.h"
#include "IEPhysicsEngine.h"
#include "IEScene.h"
#include "IEECS.h"
#include "IEInput.h"
#include "IEScriptEngine.h"
#include "IEUboManager.h"
#include "IETime.h"
#include "IEGameState.h"

IEGame::IEGame(QWidget* parent) :
    QOpenGLWidget(parent),
    format(),
    glFunc(nullptr),
    glExtraFunc(nullptr),
    systems(), systemsIndex(),
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
    glExtraFunc->glEnable(GL_STENCIL_TEST);
    glExtraFunc->glEnable(GL_MULTISAMPLE);
    glExtraFunc->glEnable(GL_BLEND);

    glExtraFunc->glDepthFunc(GL_LESS);
    glExtraFunc->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    emit initialized();
}

void IEGame::paintGL()
{
    state->onRenderFrame();
}

void IEGame::resizeGL(int w, int h)
{
    glFunc->glViewport(0, 0, w, h);

    ApplicationProperties::viewportDimensions = QVector2D(w, h);

    if(state) { state->onResize((float)w, (float)h); }
}

void IEGame::startUp()
{
    this->makeCurrent();

    appendSystem<IEInput>(new IEInput(this));
    appendSystem<IEScene>(new IEScene(this));
    appendSystem<IEScriptEngine>(new IEScriptEngine(this));
    appendSystem<IEPhysicsEngine>(new IEPhysicsEngine(this));
    appendSystem<IERenderEngine>(new IERenderEngine(this));
    appendSystem<IEECS>(new IEECS(this));
    appendSystem<IEUboManager>(new IEUboManager(this));
    appendSystem<IETime>(new IETime(this));

    foreach (auto* i, qAsConst(systems))
    {
        i->startup(*this);
    }
}

void IEGame::shutdown()
{
    this->makeCurrent();

    for(int i = systems.size() - 1; i >= 0; i--)
    {
        auto* system = systems[i];
        system->shutdown(*this);
        delete system;
        system = nullptr;
    }

    systems.clear();
    systemsIndex.clear();
}

void IEGame::onSerialize()
{
    foreach (auto* i, qAsConst(systems))
    {
        i->onSerialize(*this);
    }
}

void IEGame::onDeserialize()
{
    foreach (auto* i, qAsConst(systems))
    {
        i->onDeserialize(*this);
    }
}

void IEGame::changeState(IEGameState* val)
{
    this->makeCurrent();

    if(state)
        state->exit(*this);
    delete state;
    state = val;
    state->enter(*this);

    emit stateChanged(val);
}

bool IEGame::doesSystemExist(size_t key) const
{
    return systemsIndex.contains(key);
}

void IEGame::onUpdateFrame()
{
    state->onUpdateFrame();
}

void IEGame::onRenderFrame()
{
    this->update();
}

QDataStream& IEGame::serialize(QDataStream& out, const IESerializable& obj) const
{
    const IEGame& game = static_cast<const IEGame&>(obj);

    foreach (auto* i, qAsConst(systems))
    {
        out << *i;
    }

    out << game.systemsIndex << *game.state;

    return out;
}

QDataStream& IEGame::deserialize(QDataStream& in, IESerializable& obj)
{
    IEGame& game = static_cast<IEGame&>(obj);
    game.makeCurrent();

    foreach (auto* i, qAsConst(systems))
    {
        in >> *i;
    }

    in >> game.systemsIndex >> *game.state;

    return in;
}
