#include "IEGameStopState.h"
#include "ApplicationProperties.h"
#include "IEGame.h"
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
    glFunc(nullptr),
    glExtraFunc(nullptr),
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
    glFunc = game.getGlFunc();
    glExtraFunc = game.getGlExtraFunc();
    time = game.getSystem<IETime>();
    input = game.getSystem<IEInput>();
    ecs = game.getSystem<IEECS>();
    grEngine = game.getSystem<IERenderEngine>();

    erEngine = new ERenderEngine(this);
    eCamera = new ECamera(this);

    erEngine->startup(game);

    deserializeTemporary(game);

    IEGameState::onResize(ApplicationProperties::viewportDimensions);
}

void IEGameStopState::exit(IEGame&)
{
    serializeTemporary();
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
    grEngine->onRenderFrame(glExtraFunc, eCamera);
    erEngine->onRenderFrame(glExtraFunc, eCamera);

    time->processDeltaTime();
}

void IEGameStopState::onResize(const float w, const float h)
{
    eCamera->updateProjection(w, h);
}

void IEGameStopState::serializeTemporary()
{
    IESerialize::write<IEECS>("./resources/temp/backup/ecs.iedat", ecs);
    IESerialize::write<ECamera>("./resources/temp/backup/camera.iedat", eCamera);
}

void IEGameStopState::deserializeTemporary(IEGame& game)
{
    ecs->onDeserialize(game);

    IESerialize::read<IEECS>("./resources/temp/backup/ecs.iedat", ecs);
    IESerialize::read<ECamera>("./resources/temp/backup/camera.iedat", eCamera);

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
