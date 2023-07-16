#include "IEGame.h"
#include "ApplicationProperties.h"
#include "IEInput.h"
#include "IEScene.h"
#include "IETime.h"
#include "IEGameState.h"
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>

IEGame::IEGame(QWidget* parent) :
    QOpenGLWidget(parent),
    format(),
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
    auto* gl = QOpenGLContext::currentContext()->functions();
    auto* glExtra = QOpenGLContext::currentContext()->extraFunctions();

    gl->initializeOpenGLFunctions();
    glExtra->initializeOpenGLFunctions();

    glExtra->glEnable(GL_DEPTH_TEST);
    glExtra->glEnable(GL_STENCIL_TEST);
    glExtra->glEnable(GL_MULTISAMPLE);
    glExtra->glEnable(GL_BLEND);

    glExtra->glDepthFunc(GL_LESS);
    glExtra->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    emit initialized();
}

void IEGame::paintGL()
{
    state->onRenderFrame();
}

void IEGame::resizeGL(int w, int h)
{
    auto* gl = QOpenGLContext::currentContext()->functions();

    gl->glViewport(0, 0, w, h);

    ApplicationProperties::viewportDimensions = glm::vec2(w, h);

    if(state) { state->onResize((float)w, (float)h); }
}

void IEGame::startUp()
{
    this->makeCurrent();

    appendSystem<IEInput>(new IEInput(this));
    appendSystem<IEScene>(new IEScene(this));
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
