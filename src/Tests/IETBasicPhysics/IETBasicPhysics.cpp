#include "IETBasicPhysics.h"
#include "GameStartEvent.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEECS.h"
#include "IEECSTransformSystem.h"
#include "IEECSRenderableSystem.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"
#include "IEMesh.h"
#include "IEMaterial.h"
#include "IEShader.h"
#include "IERenderable.h"
#include "IEIndexBuffer.h"
#include "IEVertexBuffer.h"
#include "IEObjImporter.h"
#include "IEGlslImporter.h"
#include "IEHash.h"

IETBasicPhysics::IETBasicPhysics() :
    defaultAllocatorCallback(),
    defaultErrorCallback(),
    defaultDispatcher(nullptr),
    toleranceScale(),
    foundation(nullptr),
    physics(nullptr),
    scene(nullptr),
    material(nullptr)
{

}

IETBasicPhysics::~IETBasicPhysics()
{

}

void IETBasicPhysics::startup(const GameStartEvent& event)
{
    foundation = PxCreateFoundation(PX_PHYSICS_VERSION, defaultAllocatorCallback, defaultErrorCallback);
    if(!foundation)
        throw("PxCreateFoundation failed");

    toleranceScale.length = 100;
    toleranceScale.speed = 981;
    physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, toleranceScale, true);

    physx::PxSceneDesc sceneDesc(physics->getTolerancesScale());
    sceneDesc.gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);
    defaultDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
    sceneDesc.cpuDispatcher = defaultDispatcher;
    sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
    scene = physics->createScene(sceneDesc);

    material = physics->createMaterial(0.5f, 0.5f, 0.5f);

    createGround();
    createRenderable(event);
}

void IETBasicPhysics::shutdown()
{
    scene->release();
    defaultDispatcher->release();
    physics->release();
    foundation->release();
}

void IETBasicPhysics::simulate(const float dt)
{
    scene->simulate(dt);
    scene->fetchResults(true);

    updateEntities();
}

physx::PxRigidStatic* IETBasicPhysics::createStatic(const physx::PxTransform& transform,
                                                    const physx::PxGeometry& geometry)
{
    physx::PxRigidStatic* staticObj = physx::PxCreateStatic(*physics, transform, geometry, *material);
    scene->addActor(*staticObj);

    return staticObj;
}

physx::PxRigidDynamic* IETBasicPhysics::createDynamic(const physx::PxTransform& transform,
                                                      const physx::PxGeometry& geometry)
{
    physx::PxRigidDynamic* dynamicObj = physx::PxCreateDynamic(*physics, transform, geometry, *material, 10.0f);
    scene->addActor(*dynamicObj);

    return dynamicObj;
}

void IETBasicPhysics::createGround()
{
    physx::PxTransform sTransform1(0.0f, 0.0f, 0.0f);
    physx::PxBoxGeometry sGeometry1 = physx::PxBoxGeometry(1000, 0.1f, 1000);
    this->createStatic(sTransform1, sGeometry1);

    physx::PxTransform sTransform2(0.0f, 60.0f, 0.0f);
    physx::PxBoxGeometry sGeometry2 = physx::PxBoxGeometry(1000, 0.1f, 1000);
    this->createStatic(sTransform2, sGeometry2);
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
        for(int j = -15 + i; j < 15 - i; j++)
        {
            physx::PxTransform posT(j * 4, i * 4, 0.0f);
            physx::PxTransform xrotT(physx::PxQuat(qDegreesToRadians(187.0f), physx::PxVec3(1, 0, 0)));
            physx::PxTransform yrotT(physx::PxQuat(qDegreesToRadians(55.0f), physx::PxVec3(0, 1, 0)));
            physx::PxTransform zrotT(physx::PxQuat(qDegreesToRadians(55.0f), physx::PxVec3(0, 0, 1)));
            physx::PxTransform t = posT * (xrotT * yrotT * zrotT);
            physx::PxBoxGeometry dGeometry = physx::PxBoxGeometry(1.0f, 1.0f, 1.0f);
            auto* dynamicItem = this->createDynamic(t, dGeometry);
            dynamicItem->setMass(500);
            dynamicItem->setSleepThreshold(0.1f);
            dynamicItems.push_back(dynamicItem);

            auto& scene = event.getScene();
            auto& ecs = scene.getECS();
            transformSystem = ecs.getComponent<IEECSTransformSystem>("Transform");
            auto* renderableSystem = ecs.getComponent<IEECSRenderableSystem>("Renderable");

            IEEntity entity = ecs.create();
            entities.push_back(entity);

            const int transIndex = transformSystem->lookUpIndex(entity);
            transformSystem->setPosition(transIndex, QVector3D(i + 5.0f, 50.0f, 0.0f));
            transformSystem->setScale(transIndex, QVector3D(1.0f, 1.0f, 1.0f));

            const int rendIndex = ecs.attachComponent(entity, "Renderable");
            renderableSystem->setRenderableId(rendIndex, rendId);
            renderableSystem->addShown(rendIndex);
            auto* renderable = renderableSystem->getAttachedRenderable(rendIndex);
            renderable->appendMat4InstanceValue("aModel", transformSystem->getTransform(transIndex));
        }
    }
}

void IETBasicPhysics::updateEntities()
{
    for(int i = 0; i < dynamicItems.size(); i++)
    {
        physx::PxVec3 pos = dynamicItems[i]->getGlobalPose().p;
        physx::PxQuat quat = dynamicItems[i]->getGlobalPose().q;

        float angle = 0.0f;
        physx::PxVec3 rot;
        quat.toRadiansAndUnitAxis(angle, rot);

        const int transIndex = transformSystem->lookUpIndex(entities[i]);
        transformSystem->setPosition(transIndex, QVector3D(pos.x, pos.y, pos.z));
        transformSystem->setRotation(transIndex, QVector4D(rot.x, rot.y, rot.z, qRadiansToDegrees(angle)));
    }
}
