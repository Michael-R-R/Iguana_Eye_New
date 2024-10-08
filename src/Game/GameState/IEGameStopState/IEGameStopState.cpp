#include "IEGameStopState.h"
#include "ApplicationProperties.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IETime.h"
#include "IEInput.h"
#include "IERenderEngine.h"
#include "IEECS.h"
#include "IEECSTransformSystem.h"
#include "ERenderEngine.h"
#include "ECamera.h"
#include "IEFile.h"
#include "IESerialize.h"

IEGameStopState::IEGameStopState(QObject* parent) :
    IEGameState(parent),
    time(nullptr),
    input(nullptr),
    ecs(nullptr),
    grEngine(nullptr),
    erEngine(nullptr),
    eCamera(nullptr)
{

}

IEGameStopState::~IEGameStopState()
{

}

void IEGameStopState::enter(IEGame& game)
{
    auto* scene = game.getSystem<IEScene>();

    time = game.getSystem<IETime>();
    input = game.getSystem<IEInput>();
    ecs = scene->getSystem<IEECS>();
    grEngine = scene->getSystem<IERenderEngine>();

    erEngine = new ERenderEngine(this);
    eCamera = new ECamera(this);

    erEngine->startup(game);

    IEGameState::onResize(ApplicationProperties::viewportDimensions);

    deserializeTemporary(game);
}

void IEGameStopState::exit(IEGame& game)
{
    serializeTemporary(game);
}

void IEGameStopState::onUpdateFrame()
{
    const float dt = time->getDeltaTime();

    auto* tSystem = ecs->getComponent<IEECSTransformSystem>();

    eCamera->update(input, dt);
    tSystem->onUpdateFrame();
}

void IEGameStopState::onRenderFrame()
{
    grEngine->onRenderFrame(eCamera);

    erEngine->onRenderFrame(eCamera);

    time->processDeltaTime();
}

void IEGameStopState::onResize(const float w, const float h)
{
    eCamera->updateProjection(w, h);
}

QDataStream& IEGameStopState::serialize(QDataStream& out, const IESerializable& obj) const
{
    const IEGameStopState& state = static_cast<const IEGameStopState&>(obj);

    out << *state.eCamera;

    return out;
}

QDataStream& IEGameStopState::deserialize(QDataStream& in, IESerializable& obj)
{
    IEGameStopState& state = static_cast<IEGameStopState&>(obj);

    in >> *state.eCamera;

    return in;
}
