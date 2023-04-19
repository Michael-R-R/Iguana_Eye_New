#include "IEGameStopState.h"
#include "ApplicationProperties.h"
#include "IEGame.h"
#include "IEPhysicsEngine.h"
#include "IEScriptEngine.h"
#include "IEECS.h"
#include "IETime.h"
#include "IEInput.h"
#include "IERenderEngine.h"
#include "IEECSTransformSystem.h"
#include "EPhysicsEngine.h"
#include "ERenderEngine.h"
#include "ECamera.h"
#include "IEFile.h"
#include "IESerialize.h"

IEGameStopState::IEGameStopState(IEGame& game) :
    IEGameState(&game),
    glFunc(game.getGlFunc()),
    glExtraFunc(game.getGlExtraFunc()),
    time(game.getTime()),
    input(game.getInput()),
    gRenderEngine(game.getRenderEngine()),
    ecsUpdateEvent(*game.getECS()),
    ePhysicsEngine(nullptr),
    eRenderEngine(nullptr),
    eCamera(nullptr)
{

}

IEGameStopState::~IEGameStopState()
{

}

void IEGameStopState::enter(IEGame& game)
{
    ePhysicsEngine = new EPhysicsEngine(this);
    eRenderEngine = new ERenderEngine(this);
    eCamera = new ECamera(this);

    deserializeGameStates(game);

    ePhysicsEngine->startup(game);
    eRenderEngine->startup(ePhysicsEngine);

    IEGameState::onResize(ApplicationProperties::viewportDimensions);
}

void IEGameStopState::exit(IEGame& game)
{
    serializeGameStates(game);

    ePhysicsEngine->shutdown();
}

void IEGameStopState::onUpdateFrame()
{
    const float dt = time->getDeltaTime();

    eCamera->update(input, dt);
    ecsUpdateEvent.getTransform().onUpdateFrame(ecsUpdateEvent);
    ePhysicsEngine->onUpdateFrame(*input, *eCamera);
}

void IEGameStopState::onRenderFrame()
{
    eRenderEngine->onRenderPreFrame(glExtraFunc);
    gRenderEngine->onRenderFrame(glExtraFunc, eCamera);
    eRenderEngine->onRenderFrame(glExtraFunc, eCamera);
}

void IEGameStopState::onResize(const float w, const float h)
{
    eCamera->updateProjection(w, h);
}

void IEGameStopState::serializeGameStates(IEGame& game)
{
    IESerialize::write<IEECS>("./resources/temp/backup/ecs.iedat", game.getECS());
    IESerialize::write<ECamera>("./resources/temp/backup/camera.iedat", &(*eCamera));
}

void IEGameStopState::deserializeGameStates(IEGame& game)
{
    IESerialize::read<IEECS>("./resources/temp/backup/ecs.iedat", game.getECS());
    IESerialize::read<ECamera>("./resources/temp/backup/camera.iedat", &(*eCamera));

    IEFile::removeAllFiles("./resources/temp/backup/");
}

QDataStream& IEGameStopState::serialize(QDataStream& out, const Serializable& obj) const
{
    const IEGameStopState& state = static_cast<const IEGameStopState&>(obj);

    out << *state.eCamera;

    return out;
}

QDataStream& IEGameStopState::deserialize(QDataStream& in, Serializable& obj)
{
    IEGameStopState& state = static_cast<IEGameStopState&>(obj);

    in >> *state.eCamera;

    return in;
}
