#include "IETBasicPhysics.h"
#include "ApplicationProperties.h"
#include "GameStartEvent.h"
#include "IEGame.h"
#include "IEInput.h"
#include "IEScene.h"
#include "IEECS.h"
#include "IEECSTransformSystem.h"
#include "IEECSRenderableSystem.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"
#include "IECameraManager.h"
#include "IECamera.h"
#include "IEMesh.h"
#include "IEMaterial.h"
#include "IEShader.h"
#include "IERenderable.h"
#include "IEIndexBuffer.h"
#include "IEVertexBuffer.h"
#include "IEObjImporter.h"
#include "IEGlslImporter.h"
#include "IEHash.h"

void ContactReportCallback::onWake(physx::PxActor** actors, physx::PxU32 count)
{
    while(count--)
    {
        qDebug() << "Wake:" << (int)(size_t)actors[count]->userData;
    }
}

void ContactReportCallback::onSleep(physx::PxActor** actors, physx::PxU32 count)
{
    while(count--)
    {
        qDebug() << "Sleep:" << (int)(size_t)actors[count]->userData;
    }
}

void ContactReportCallback::onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count)
{
    while(count--)
    {
        const physx::PxTriggerPair& current = *pairs++;
        if(current.status & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
        {
            qDebug() << "On Trigger Enter(trigger actor):" << (int)(size_t)current.triggerActor->userData;
            qDebug() << "On Trigger Enter(other actor):" << (int)(size_t)current.otherActor->userData;
        }
        if(current.status & physx::PxPairFlag::eNOTIFY_TOUCH_LOST)
        {
            qDebug() << "On Trigger Exit(trigger actor):" << (int)(size_t)current.triggerActor->userData;
            qDebug() << "On Trigger Exit(other actor):" << (int)(size_t)current.otherActor->userData;
        }
    }
}

IETBasicPhysics::IETBasicPhysics() :
    reportCallback(),
    defaultAllocatorCallback(),
    defaultErrorCallback(),
    defaultDispatcher(nullptr),
    toleranceScale(),
    pxFoundation(nullptr),
    pxPhysics(nullptr),
    pxScene(nullptr),
    pxMaterial(nullptr)
{

}

IETBasicPhysics::~IETBasicPhysics()
{

}

void IETBasicPhysics::startup(const GameStartEvent& event)
{
    pxFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, defaultAllocatorCallback, defaultErrorCallback);
    if(!pxFoundation)
        throw("PxCreateFoundation failed");

    toleranceScale.length = 100;
    toleranceScale.speed = 981;
    pxPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *pxFoundation, toleranceScale, true);

    physx::PxSceneDesc sceneDesc(pxPhysics->getTolerancesScale());
    sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
    defaultDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
    sceneDesc.cpuDispatcher = defaultDispatcher;
    sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
    sceneDesc.simulationEventCallback = &reportCallback;

    pxScene = pxPhysics->createScene(sceneDesc);
    pxMaterial = pxPhysics->createMaterial(1.0f, 1.0f, 0.5f);

    createGround();
    createRenderable(event);
    game = &event.getGame();
    input = &event.getInput();
    cameraManager = &event.getScene().getCameraManager();
}

void IETBasicPhysics::shutdown()
{
    pxScene->release();
    defaultDispatcher->release();
    pxPhysics->release();
    pxFoundation->release();
}

void IETBasicPhysics::simulate(const float dt)
{
    accumulator += dt;
    if(accumulator < stepSize)
        return;

    accumulator -= stepSize;

    pxScene->simulate(stepSize);
    pxScene->fetchResults(true);

    updateEntities();
    castRay();
}

void IETBasicPhysics::createGround()
{
    physx::PxTransform t1(0.0f, 0.0f, 0.0f);
    physx::PxBoxGeometry b1 = physx::PxBoxGeometry(1000, 0.1f, 1000);
    auto obj1 = std::make_unique<IEBoxCollider>(*pxPhysics, *pxMaterial, b1, t1, -1);
    //obj1->setIsTrigger(true);
    pxScene->addActor(*obj1->getActor());
    boxColliders.push_back(std::move(obj1));

    physx::PxTransform t2(0.0f, 60.0f, 0.0f);
    physx::PxBoxGeometry b2 = physx::PxBoxGeometry(1000, 0.1f, 1000);
    auto obj2 = std::make_unique<IEBoxCollider>(*pxPhysics, *pxMaterial, b2, t2, -2);
    pxScene->addActor(*obj2->getActor());
    boxColliders.push_back(std::move(obj2));
}

void IETBasicPhysics::createRenderable(const GameStartEvent& event)
{
    auto& scene = event.getScene();
    auto& meshManager = scene.getMeshManager();
    auto& materialManager = scene.getMaterialManager();
    auto& shaderManager = scene.getShaderManager();
    auto& renderableManager = scene.getRenderableManager();

    QString path = "./resources/meshes/tests/cube.obj";
    unsigned long long meshId = IEHash::Compute(path);
    auto mesh = std::make_unique<IEMesh>(path, meshId);
    mesh->setType(IEResource::Type::Editor);
    IEObjImporter::importMesh(path, *mesh);

    path = "./resources/materials/tests/mat.iemat";
    unsigned long long materialId = IEHash::Compute(path);
    auto material = std::make_unique<IEMaterial>(path, materialId);
    material->setType(IEResource::Type::Editor);
    IEUniform uniform;
    uniform.add("uColor", QColor(0, 0, 255, 255));
    material->setUniformData(uniform);

    path = "./resources/shaders/tests/instanced_renderable.glsl";
    unsigned long long shaderId = IEHash::Compute(path);
    auto shader = std::make_unique<IEShader>(path, shaderId);
    shader->setType(IEResource::Type::Editor);
    IEGlslImporter::importGlsl(path, *shader);
    shader->build();

    path = "./resources/renderables/tests/rend.ierend";
    unsigned long long renderableId = IEHash::Compute(path);
    auto renderable = std::make_unique<IERenderable>(path, renderableId,
                                                     meshId,
                                                     materialId,
                                                     shaderId);
    renderable->setType(IEResource::Type::Editor);
    renderable->setDrawType(GL_TRIANGLES);
    renderable->setRenderType(IERenderable::RenderType::I_Index);

    auto indexBuffer = std::make_unique<IEIndexBuffer>(mesh->getIndices());
    renderable->addIndexBuffer(std::move(indexBuffer));

    auto posBuffer = std::make_unique<IEVertexBuffer<QVector3D>>(mesh->getPosVertices(), 12, 3, 0, 0, 0);
    renderable->addVec3Buffer("aPos", std::move(posBuffer));

    auto modelBuffer = std::make_unique<IEVertexBuffer<QMatrix4x4>>(QVector<QMatrix4x4>{QMatrix4x4()}, 64, 4, 64, 4, 16);
    renderable->addMat4Buffer("aModel", std::move(modelBuffer));

    renderable->build(*shader);

    meshManager.add(meshId, std::move(mesh));
    materialManager.add(materialId, std::move(material));
    shaderManager.add(shaderId, std::move(shader));
    renderableManager.add(renderableId, std::move(renderable));

    createEntities(event, renderableId);
}

void IETBasicPhysics::createEntities(const GameStartEvent& event, const unsigned long long rendId)
{
    for(int i = 1; i < 10; i++)
    {
        for(int j = -5 + i; j < 5 - i; j++)
        {
//            auto& scene = event.getScene();
//            auto& ecs = scene.getECS();
//            transformSystem = ecs.getComponent<IEECSTransformSystem>("Transform");
//            auto* renderableSystem = ecs.getComponent<IEECSRenderableSystem>("Renderable");

//            auto entity = ecs.create();

//            const int transIndex = transformSystem->lookUpIndex(entity);
//            transformSystem->setPosition(transIndex, QVector3D(i + 5.0f, 50.0f, 0.0f));
//            transformSystem->setScale(transIndex, QVector3D(1.0f, 1.0f, 1.0f));

//            const int rendIndex = ecs.attachComponent(entity, "Renderable");
//            renderableSystem->setRenderableId(rendIndex, rendId);
//            renderableSystem->addShown(rendIndex);
//            auto* renderable = renderableSystem->getAttachedRenderable(rendIndex);
//            renderable->appendMat4InstanceValue("aModel", transformSystem->getTransform(transIndex));

//            physx::PxTransform posT(j * 4, i * 4, 0.0f);
//            physx::PxTransform xrotT(physx::PxQuat(qDegreesToRadians(187.0f), physx::PxVec3(1, 0, 0)));
//            physx::PxTransform yrotT(physx::PxQuat(qDegreesToRadians(55.0f), physx::PxVec3(0, 1, 0)));
//            physx::PxTransform zrotT(physx::PxQuat(qDegreesToRadians(55.0f), physx::PxVec3(0, 0, 1)));
//            physx::PxTransform t = posT * (xrotT * yrotT * zrotT);
//            physx::PxBoxGeometry dGeometry = physx::PxBoxGeometry(1.0f, 1.0f, 1.0f);
//            auto dynamicObj = std::make_unique<IERigidBody>(*pxPhysics,
//                                                            *pxMaterial,
//                                                            t, dGeometry,
//                                                            200.0f, 0.1f,
//                                                            entity.getId());

//            pxScene->addActor(*dynamicObj->getActor());

//            dynamicBodies.push_back(std::move(dynamicObj));
//            entities.push_back(entity);
        }
    }
}

void IETBasicPhysics::updateEntities()
{
    for(int i = 0; i < dynamicBodies.size(); i++)
    {
        if(dynamicBodies[i]->getBodyType() == IERigidBody::BodyType::Static)
            continue;

        physx::PxVec3 pos = dynamicBodies[i]->getActor()->getGlobalPose().p;
        physx::PxQuat quat = dynamicBodies[i]->getActor()->getGlobalPose().q;

        float angle = 0.0f;
        physx::PxVec3 rot;
        quat.toRadiansAndUnitAxis(angle, rot);

        const int transIndex = transformSystem->lookUpIndex(entities[i]);
        transformSystem->setPosition(transIndex, QVector3D(pos.x, pos.y, pos.z));
        transformSystem->setRotation(transIndex, QVector4D(rot.x, rot.y, rot.z, qRadiansToDegrees(angle)));
    }
}

QVector3D IETBasicPhysics::scrPosToWorldRay()
{
    QVector2D cursorPos = input->cursorPos();
    QVector2D dimension = ApplicationProperties::viewportDimensions;

    auto cameraId = cameraManager->getDefaultResourceId();
    auto* camera = cameraManager->value(cameraId);
    QMatrix4x4 projection = camera->getProjection();
    QMatrix4x4 view = camera->getView();

    // Normal device coords
    const float x = (2.0f * cursorPos.x()) / dimension.x() - 1.0f;
    const float y = 1.0f - (2.0f * cursorPos.y()) / dimension.y();
    const float z = 1.0f;
    QVector3D rayNDC = QVector3D(x, y, z);

    // 4D homogenous clip coords
    QVector4D rayClip = QVector4D(rayNDC.x(), rayNDC.y(), -1.0f, 1.0f);

    // 4D eye coords
    QVector4D rayEye = projection.inverted() * rayClip;
    rayEye = QVector4D(rayEye.x(), rayEye.y(), -1.0f, 0.0f);

    // 4D world coords
    QVector4D inverseMat = view.inverted() * rayEye;
    QVector3D rayWorld = QVector3D(inverseMat.x(), inverseMat.y(), inverseMat.z());

    return rayWorld.normalized();
}

void IETBasicPhysics::castRay()
{
    if(input->isPressed("Left Click"))
    {
        QVector3D qDir = scrPosToWorldRay();

        physx::PxVec3 origin(0.0f, 15.0f, 20.0f);
        physx::PxVec3 dir(qDir.x(), qDir.y(), qDir.z());
        physx::PxReal maxDistance = 1000.0f;
        physx::PxRaycastBuffer hit;

        bool status = pxScene->raycast(origin, dir, maxDistance, hit);
        if(status)
        {
            auto* actor = hit.block.actor;
            if(actor->is<physx::PxRigidDynamic>())
            {
                qDebug() << "Hit: " << (int)(size_t)actor->userData;
            }
        }
        else
            qDebug() << "No hit";
    }
}
