#include "IETIslandGenerator.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEObjImporter.h"
#include "IEGlslImporter.h"
#include "IEHash.h"

IETIslandGenerator::IETIslandGenerator(IEGame* game) :
    world(), dropZone(), particle()
{
    auto scene = game->getIEScene();

    QString path = "./resources/meshes/tests/cube.obj";
    unsigned long long id = IEHash::Compute(path);
    auto mesh = new IEMesh(path, id);
    IEObjImporter::importMesh(path, mesh);
    scene->getMeshManager()->add(id, mesh);

    path = "./resources/shaders/tests/instanced_renderable.glsl";
    id = IEHash::Compute(path);
    auto shader = new IEShader(path, id);
    IEGlslImporter::importGlsl(path, shader);
    shader->build();
    scene->getShaderManager()->add(id, shader);

    buildDeepWaterRenderable(mesh, shader, scene);
    buildShallowWaterRenderable(mesh, shader, scene);
    buildSandRenderable(mesh, shader, scene);
    buildGrassRenderable(mesh, shader, scene);
    buildForestRenderable(mesh, shader, scene);
    buildMountainRenderable(mesh, shader, scene);

    setupParameters();
    setupWorld();
}

void IETIslandGenerator::run(IEGame* game)
{

}

void IETIslandGenerator::buildDeepWaterRenderable(IEMesh* mesh, IEShader* shader, IEScene* scene)
{
    QString path = "./resources/materials/tests/deepwater.iemat";
    unsigned long long id = IEHash::Compute(path);
    auto material = new IEMaterial(path, id);
    IEUniform deepwaterUniform;
    deepwaterUniform.add("uColor", QColor(0, 20, 179, 255));
    material->setUniformData(deepwaterUniform);
    scene->getMaterialManager()->add(id, material);

    path = QString("./resources/renderables/tests/%1/%2/%3/deepwater.ierend")
            .arg(QString::number(mesh->getId()),
                 QString::number(material->getId()),
                 QString::number(shader->getId()));
    id = IEHash::Compute(path);
    deepWaterId = id;

    auto renderable = new IERenderable(path, id, mesh->getId(), material->getId(), shader->getId());
    renderable->setRenderType(IERenderable::RenderType::I_Index);

    auto indexBuffer = new IEIndexBuffer(mesh->getIndices());
    auto posBuffer = new IEVertexBuffer<QVector3D>(mesh->getPosVertices(), 12, 3, 0, 0, 0);
    auto modelBuffer = new IEVertexBuffer<QMatrix4x4>(QVector<QMatrix4x4>(), 64, 4, 64, 4, 16);
    renderable->addIndexBuffer(indexBuffer);
    renderable->addVec3Buffer("aPos", posBuffer);
    renderable->addMat4Buffer("aModel", modelBuffer);
    renderable->build(shader);
    scene->getRenderableManager()->add(id, renderable);
}

void IETIslandGenerator::buildShallowWaterRenderable(IEMesh* mesh, IEShader* shader, IEScene* scene)
{
    QString path = "./resources/materials/tests/shallowwater.iemat";
    unsigned long long id = IEHash::Compute(path);
    auto material = new IEMaterial(path, id);
    IEUniform shallowwaterUniform;
    shallowwaterUniform.add("uColor", QColor(48, 177, 255, 255));
    material->setUniformData(shallowwaterUniform);
    scene->getMaterialManager()->add(id, material);

    path = QString("./resources/renderables/tests/%1/%2/%3/shallowwater.ierend")
            .arg(QString::number(mesh->getId()),
                 QString::number(material->getId()),
                 QString::number(shader->getId()));
    id = IEHash::Compute(path);
    shallowWaterId = id;

    auto renderable = new IERenderable(path, id, mesh->getId(), material->getId(), shader->getId());
    renderable->setRenderType(IERenderable::RenderType::I_Index);

    auto indexBuffer = new IEIndexBuffer(mesh->getIndices());
    auto posBuffer = new IEVertexBuffer<QVector3D>(mesh->getPosVertices(), 12, 3, 0, 0, 0);
    auto modelBuffer = new IEVertexBuffer<QMatrix4x4>(QVector<QMatrix4x4>(), 64, 4, 64, 4, 16);
    renderable->addIndexBuffer(indexBuffer);
    renderable->addVec3Buffer("aPos", posBuffer);
    renderable->addMat4Buffer("aModel", modelBuffer);
    renderable->build(shader);
    scene->getRenderableManager()->add(id, renderable);
}

void IETIslandGenerator::buildSandRenderable(IEMesh* mesh, IEShader* shader, IEScene* scene)
{
    QString path = "./resources/materials/tests/sand.iemat";
    unsigned long long id = IEHash::Compute(path);
    auto material = new IEMaterial(path, id);
    IEUniform sandUniform;
    sandUniform.add("uColor", QColor(255, 194, 39, 255));
    material->setUniformData(sandUniform);
    scene->getMaterialManager()->add(id, material);

    path = QString("./resources/renderables/tests/%1/%2/%3/sand.ierend")
            .arg(QString::number(mesh->getId()),
                 QString::number(material->getId()),
                 QString::number(shader->getId()));
    id = IEHash::Compute(path);
    sandId = id;

    auto renderable = new IERenderable(path, id, mesh->getId(), material->getId(), shader->getId());
    renderable->setRenderType(IERenderable::RenderType::I_Index);

    auto indexBuffer = new IEIndexBuffer(mesh->getIndices());
    auto posBuffer = new IEVertexBuffer<QVector3D>(mesh->getPosVertices(), 12, 3, 0, 0, 0);
    auto modelBuffer = new IEVertexBuffer<QMatrix4x4>(QVector<QMatrix4x4>(), 64, 4, 64, 4, 16);
    renderable->addIndexBuffer(indexBuffer);
    renderable->addVec3Buffer("aPos", posBuffer);
    renderable->addMat4Buffer("aModel", modelBuffer);
    renderable->build(shader);
    scene->getRenderableManager()->add(id, renderable);
}

void IETIslandGenerator::buildGrassRenderable(IEMesh* mesh, IEShader* shader, IEScene* scene)
{
    QString path = "./resources/materials/tests/grass.iemat";
    unsigned long long id = IEHash::Compute(path);
    auto material = new IEMaterial(path, id);
    IEUniform grassUniform;
    grassUniform.add("uColor", QColor(91, 162, 131, 255));
    material->setUniformData(grassUniform);
    scene->getMaterialManager()->add(id, material);

    path = QString("./resources/renderables/tests/%1/%2/%3/grass.ierend")
            .arg(QString::number(mesh->getId()),
                 QString::number(material->getId()),
                 QString::number(shader->getId()));
    id = IEHash::Compute(path);
    grassId = id;

    auto renderable = new IERenderable(path, id, mesh->getId(), material->getId(), shader->getId());
    renderable->setRenderType(IERenderable::RenderType::I_Index);

    auto indexBuffer = new IEIndexBuffer(mesh->getIndices());
    auto posBuffer = new IEVertexBuffer<QVector3D>(mesh->getPosVertices(), 12, 3, 0, 0, 0);
    auto modelBuffer = new IEVertexBuffer<QMatrix4x4>(QVector<QMatrix4x4>(), 64, 4, 64, 4, 16);
    renderable->addIndexBuffer(indexBuffer);
    renderable->addVec3Buffer("aPos", posBuffer);
    renderable->addMat4Buffer("aModel", modelBuffer);
    renderable->build(shader);
    scene->getRenderableManager()->add(id, renderable);
}

void IETIslandGenerator::buildForestRenderable(IEMesh* mesh, IEShader* shader, IEScene* scene)
{
    QString path = "./resources/materials/tests/forest.iemat";
    unsigned long long id = IEHash::Compute(path);
    auto material = new IEMaterial(path, id);
    IEUniform forestUniform;
    forestUniform.add("uColor", QColor(79, 90, 81, 255));
    material->setUniformData(forestUniform);
    scene->getMaterialManager()->add(id, material);

    path = QString("./resources/renderables/tests/%1/%2/%3/forest.ierend")
            .arg(QString::number(mesh->getId()),
                 QString::number(material->getId()),
                 QString::number(shader->getId()));
    id = IEHash::Compute(path);
    forestId = id;

    auto renderable = new IERenderable(path, id, mesh->getId(), material->getId(), shader->getId());
    renderable->setRenderType(IERenderable::RenderType::I_Index);

    auto indexBuffer = new IEIndexBuffer(mesh->getIndices());
    auto posBuffer = new IEVertexBuffer<QVector3D>(mesh->getPosVertices(), 12, 3, 0, 0, 0);
    auto modelBuffer = new IEVertexBuffer<QMatrix4x4>(QVector<QMatrix4x4>(), 64, 4, 64, 4, 16);
    renderable->addIndexBuffer(indexBuffer);
    renderable->addVec3Buffer("aPos", posBuffer);
    renderable->addMat4Buffer("aModel", modelBuffer);
    renderable->build(shader);
    scene->getRenderableManager()->add(id, renderable);
}

void IETIslandGenerator::buildMountainRenderable(IEMesh* mesh, IEShader* shader, IEScene* scene)
{
    QString path = "./resources/materials/tests/mountain.iemat";
    unsigned long long id = IEHash::Compute(path);
    auto material = new IEMaterial(path, id);
    IEUniform mountainUniform;
    mountainUniform.add("uColor", QColor(103, 109, 122, 255));
    material->setUniformData(mountainUniform);
    scene->getMaterialManager()->add(id, material);

    path = QString("./resources/renderables/tests/%1/%2/%3/mountain.ierend")
            .arg(QString::number(mesh->getId()),
                 QString::number(material->getId()),
                 QString::number(shader->getId()));
    id = IEHash::Compute(path);
    mountainId = id;

    auto renderable = new IERenderable(path, id, mesh->getId(), material->getId(), shader->getId());
    renderable->setRenderType(IERenderable::RenderType::I_Index);

    auto indexBuffer = new IEIndexBuffer(mesh->getIndices());
    auto posBuffer = new IEVertexBuffer<QVector3D>(mesh->getPosVertices(), 12, 3, 0, 0, 0);
    auto modelBuffer = new IEVertexBuffer<QMatrix4x4>(QVector<QMatrix4x4>(), 64, 4, 64, 4, 16);
    renderable->addIndexBuffer(indexBuffer);
    renderable->addVec3Buffer("aPos", posBuffer);
    renderable->addMat4Buffer("aModel", modelBuffer);
    renderable->build(shader);
    scene->getRenderableManager()->add(id, renderable);
}

void IETIslandGenerator::setupParameters()
{
    world.width = 20;
    world.height = 20;
    world.particleAmount = 100;
    world.waterline = 70;

    dropZone.centerX = 10;
    dropZone.centerY = 10;
    dropZone.radius = 9;

    particle.lifeTime = 100;
}

void IETIslandGenerator::setupWorld()
{
    world.landZone = 255 - world.waterline;

    for (int row = 0; row < world.height; row++)
    {
        world.valueArray.append(QVector<int>(world.width));
    }

    for (int row = 0; row < world.height; row++)
    {
        for (int col = 0; col < world.width; col++)
        {
            world.valueArray[row][col] = 0;
        }
    }

    world.particleArray = QVector<Particle>(world.particleAmount);
    for (int i = 0; i < world.particleAmount; i++)
    {
        this->calcDropZone(world.width, world.height);

        world.particleArray[i].lifeTime = particle.lifeTime;
        world.particleArray[i].currXLoc = dropZone.xDropLoc;
        world.particleArray[i].currYLoc = dropZone.yDropLoc;
    }
}

void IETIslandGenerator::calcDropZone(int w, int h)
{
    double r = dropZone.radius * sqrt(IERandomNumber::randDouble(0.0, 1.0));
    double theta = IERandomNumber::randDouble(0.0, 1.0) * 2 * 3.14;
    dropZone.xDropLoc = (int)(dropZone.centerX + r * cos(theta));
    dropZone.yDropLoc = (int)(dropZone.centerY + r * sin(theta));

    if (dropZone.xDropLoc < 0) { dropZone.xDropLoc = 0; }
    else if (dropZone.xDropLoc >= w) { dropZone.xDropLoc = w - 1; }

    if (dropZone.yDropLoc < 0) { dropZone.yDropLoc = 0; }
    else if (dropZone.yDropLoc >= h) { dropZone.yDropLoc = h - 1; }
}
