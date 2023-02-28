#include "IETCreateInstancedRenderable.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEObjImporter.h"
#include "IEGlslImporter.h"
#include "IEHash.h"

IETCreateInstancedRenderable::IETCreateInstancedRenderable(IEGame* game) :
    row(0)
{
    auto scene = game->getIEScene();

    QString path = "./resources/meshes/tests/triangle.obj";
    unsigned long long id = IEHash::Compute(path);
    auto mesh = new IEMesh(path, id);
    IEObjImporter::importMesh(path, mesh);
    scene->getMeshManager()->add(id, mesh);

    path = "./resources/materials/tests/default.iemat";
    id = IEHash::Compute(path);
    auto material = new IEMaterial(path, id);
    scene->getMaterialManager()->add(id, material);

    path = "./resources/shaders/tests/instanced_renderable.glsl";
    id = IEHash::Compute(path);
    auto shader = new IEShader(path, id);
    IEGlslImporter::importGlsl(path, shader);
    shader->build();
    scene->getShaderManager()->add(id, shader);

    path = "./resources/renderables/tests/instanced_renderable.ierend";
    id = IEHash::Compute(path);
    auto renderable = new IERenderable(path, id);
    renderable->setRenderType(IERenderable::RenderType::I_Index);
    renderable->setMeshId(mesh->getId());
    renderable->setMaterialId(material->getId());
    renderable->setShaderId(shader->getId());

    auto uniformData = IEUniform();
    uniformData.add("uScale", QVector2D(0.1f, 0.1f));
    renderable->setUniformData(uniformData);

    auto indexBuffer = new IEIndexBuffer(mesh->getIndices());
    auto posBuffer = new IEVertexBuffer<QVector3D>(mesh->getPosVertices(), 3);
    auto offsetBuffer = new IEVertexBuffer<QVector2D>(QVector<QVector2D>(), 2, 0, 1);
    renderable->addIndexBuffer(indexBuffer);
    renderable->addVec3Buffer("aPos", posBuffer);
    renderable->addVec2Buffer("aOffset", offsetBuffer);
    renderable->build(shader);
    scene->getRenderableManager()->add(id, renderable);
}

void IETCreateInstancedRenderable::run(IEGame* game)
{
    auto scene = game->getIEScene();
    auto ecs = scene->getECS();
    auto nameSystem = ecs->getComponent<IEECSNameSystem>(IEComponentType::Name);
    auto renderableSystem = ecs->getComponent<IEECSRenderableSystem>(IEComponentType::Renderable);

    auto renderable = scene->getRenderableManager()->getValue(IEHash::Compute("./resources/renderables/tests/instanced_renderable.ierend"));

    int end = row + 10;
    for(; row < end; row++)
    {
        for(int col = 0; col < 101; col++)
        {
            IEEntity entity = ecs->create();
            int nameIndex = nameSystem->lookUpIndex(entity);
            nameSystem->setName(nameIndex, "Test_" + QString::number(row + col));

            int index = ecs->attachComponent(entity, IEComponentType::Renderable);
            renderableSystem->setRenderableId(index, renderable->getId());
            renderableSystem->addShown(index);

            QVector2D offset(row * 0.1f, col * 0.1f);
            renderable->addShownInstance();
            renderable->appendVec2InstanceValue("aOffset", offset);
        }
    }

    row = (row > 101) ? 0 : row;
}

void IETCreateInstancedRenderable::oneShot(IEGame* game)
{
    auto scene = game->getIEScene();
    auto ecs = scene->getECS();
    auto nameSystem = ecs->getComponent<IEECSNameSystem>(IEComponentType::Name);
    auto renderableSystem = ecs->getComponent<IEECSRenderableSystem>(IEComponentType::Renderable);

    auto renderable = scene->getRenderableManager()->getValue(IEHash::Compute("./resources/renderables/tests/instanced_renderable.ierend"));

    for(int i = -10; i < 11; i++)
    {
        for(int j = -10; j < 11; j++)
        {
            IEEntity entity = ecs->create();
            int nameIndex = nameSystem->lookUpIndex(entity);
            nameSystem->setName(nameIndex, "Test_" + QString::number(i + j));

            int index = ecs->attachComponent(entity, IEComponentType::Renderable);
            renderableSystem->setRenderableId(index, renderable->getId());
            renderableSystem->addShown(index);

            QVector2D offset(i * 0.1f, j * 0.1f);
            renderable->appendVec2InstanceValue("aOffset", offset);
        }
    }
}











