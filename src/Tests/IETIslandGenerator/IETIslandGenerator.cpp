#include "IETIslandGenerator.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEObjImporter.h"
#include "IEGlslImporter.h"
#include "IEHash.h"
#include <iostream>

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
    generateWorld();
    normalizeValues();
    translateWorld(game);
}

void IETIslandGenerator::run(IEGame*)
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
    world.width = 100;
    world.height = 100;
    world.particleAmount = 500;
    world.waterline = 70;

    dropZone.centerX = 50;
    dropZone.centerY = 50;
    dropZone.radius = 5;

    particle.lifeTime = 1000;
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

void IETIslandGenerator::generateWorld()
{
    // Simulate each particle
    for (int i = 0; i < world.particleAmount; i++)
    {
        // First time dropping in, so increment world index value
        int xLoc = world.particleArray[i].currXLoc;
        int yLoc = world.particleArray[i].currYLoc;
        world.valueArray[yLoc][xLoc]++;

        // Simulate individual particle until it dies
        while (world.particleArray[i].lifeTime > 0)
        {
            // Get new location
            QPair<int, int> newMoveLoc = getParticleLoc(world.particleArray[i]);

            if (newMoveLoc.first != -1) // Has valid move
            {
                // Move particle
                world.particleArray[i].currXLoc = newMoveLoc.first;
                world.particleArray[i].currYLoc = newMoveLoc.second;

                // Increase world index by 1
                int xLoc = world.particleArray[i].currXLoc;
                int yLoc = world.particleArray[i].currYLoc;
                world.valueArray[yLoc][xLoc]++;

                // Decrease particle lifetime by 1
                world.particleArray[i].lifeTime--;
            }
            else // Doesn't have any valid moves
            {
                // Kill the particle (Chk...Chk...Click...Bam)
                world.particleArray[i].lifeTime = 0;
            }
        }
    }
}

QPair<int, int> IETIslandGenerator::getParticleLoc(const Particle& particle)
{
    QVector<QPair<int, int>> validMoves;

    int currIndexVal = world.valueArray[particle.currYLoc][particle.currXLoc];

    int xLoc = 0;
    int yLoc = 0;

    // Check north
    xLoc = particle.currXLoc;
    yLoc = particle.currYLoc - 1;
    checkIfValidMove(validMoves, xLoc, yLoc, currIndexVal);

    // Check north east
    xLoc = particle.currXLoc + 1;
    yLoc = particle.currYLoc - 1;
    checkIfValidMove(validMoves, xLoc, yLoc, currIndexVal);

    // Check east
    xLoc = particle.currXLoc + 1;
    yLoc = particle.currYLoc;
    checkIfValidMove(validMoves, xLoc, yLoc, currIndexVal);

    // Check south east
    xLoc = particle.currXLoc + 1;
    yLoc = particle.currYLoc + 1;
    checkIfValidMove(validMoves, xLoc, yLoc, currIndexVal);

    // Check south
    xLoc = particle.currXLoc;
    yLoc = particle.currYLoc + 1;
    checkIfValidMove(validMoves, xLoc, yLoc, currIndexVal);

    // Check south west
    xLoc = particle.currXLoc - 1;
    yLoc = particle.currYLoc + 1;
    checkIfValidMove(validMoves, xLoc, yLoc, currIndexVal);

    // Check west
    xLoc = particle.currXLoc - 1;
    yLoc = particle.currYLoc;
    checkIfValidMove(validMoves, xLoc, yLoc, currIndexVal);

    // Check north west
    xLoc = particle.currXLoc - 1;
    yLoc = particle.currYLoc - 1;
    checkIfValidMove(validMoves, xLoc, yLoc, currIndexVal);

    // Randomly pick a valid move from
    // the pair array
    if (validMoves.size() > 0)
    {
        int randomNumber = IERandomNumber::randInt(0, validMoves.size() - 1);

        QPair<int, int> validMove;
        validMove.first = validMoves[randomNumber].first;
        validMove.second  = validMoves[randomNumber].second;
        return validMove;
    }
    // No valid moves to pick from
    else
    {
        QPair<int, int> validMove;
        validMove.first = -1;
        validMove.second  = -1;
        return validMove;
    }

    return QPair<int, int>(-1, -1);
}

void IETIslandGenerator::checkIfValidMove(QVector<QPair<int, int>>& validMoves, int xLoc, int yLoc, int currIndexVal)
{
    if ((xLoc >= 0 && xLoc < world.width) && (yLoc >= 0 && yLoc < world.height)) // Valid move
    {
        // Adjacent value <= current index value
        if (world.valueArray[yLoc][xLoc] <= currIndexVal)
        {
            validMoves.append(QPair<int, int>(yLoc, xLoc));
        }
    }
}

void IETIslandGenerator::normalizeValues()
{
    int maxValue = findMaxValue();

    for (int row = 0; row < world.height; row++)
    {
        for (int col = 0; col < world.width; col++)
        {
            int value = world.valueArray[row][col];
            double normVal = ((double)value / (double)maxValue) * 255;

            world.valueArray[row][col] = (int)normVal;
        }
    }
}

int IETIslandGenerator::findMaxValue()
{
    int maxValue = world.valueArray[0][0];

    for (int row = 1; row < world.height; row++)
    {
        for (int col = 1; col < world.width; col++)
        {
            int value = world.valueArray[row][col];
            if (maxValue < value)
            {
                maxValue = value;
            }
        }
    }

    return maxValue;
}

void IETIslandGenerator::translateWorld(IEGame* game)
{
    double landZone = (double)world.landZone;
    double waterLine = (double)world.waterline;

    for (int row = 0; row < world.height; row++)
    {
        for (int col = 0; col < world.width; col++)
        {
            int value = world.valueArray[row][col];

            if (value < (0.4 * waterLine)) { createDeepWaterEntity(row, col, game); }
            else if(value >= (0.4 * waterLine) && value <= waterLine) { createShallowWaterEntity(row, col, game); }
            else if(value < (waterLine + (0.10 * landZone))) { createSandEntity(row, col,  game); }
            else if(value >= (waterLine + (0.10 * landZone)) && value < (waterLine + (0.50 * landZone))) { createGrassEntity(row, col, game); }
            else if (value >= (waterLine + (0.50 * landZone)) && value < (waterLine + (0.80 * landZone))) { createForestEntity(row, col, game); }
            else { createMountainEntity(row, col, game); }
        }
    }
}

void IETIslandGenerator::printWorld()
{
    for (int row = 0; row < world.height; row++)
    {
        for (int col = 0; col < world.width; col++)
        {
            std::cout << std::setw(4) << world.valueArray[row][col];
        }
        std::cout << "\n";
    }

    std::cout << "\n";
}

void IETIslandGenerator::createDeepWaterEntity(const int row, const int col, IEGame* game)
{
    for(int i = -10; i < 1; i++)
    {
        createEntity(row, col, i, deepWaterId, game);
    }
}

void IETIslandGenerator::createShallowWaterEntity(const int row, const int col, IEGame* game)
{
    createEntity(row, col, 0, shallowWaterId, game);
}

void IETIslandGenerator::createSandEntity(const int row, const int col, IEGame* game)
{
    for(int i = 0; i < 2; i++)
    {
        createEntity(row, col, i, sandId, game);
    }
}

void IETIslandGenerator::createGrassEntity(const int row, const int col, IEGame* game)
{
    for(int i = 0; i < 2; i++)
    {
        createEntity(row, col, i, grassId, game);
    }
}

void IETIslandGenerator::createForestEntity(const int row, const int col, IEGame* game)
{
    for(int i = 0; i < 4; i++)
    {
        createEntity(row, col, 0, forestId, game);
    }
}

void IETIslandGenerator::createMountainEntity(const int row, const int col, IEGame* game)
{
    for(int i = 0; i < 6; i++)
    {
        createEntity(row, col, 0, mountainId, game);
    }
}

void IETIslandGenerator::createEntity(const int row, const int col, const int value,
                                      const unsigned long long id, IEGame* game)
{
    auto ecs = game->getIEScene()->getECS();
    auto nameSystem = ecs->getComponent<IEECSNameSystem>(IEComponentType::Name);
    auto renderableSystem = ecs->getComponent<IEECSRenderableSystem>(IEComponentType::Renderable);
    auto transformSystem = ecs->getComponent<IEECSTransformSystem>(IEComponentType::Transform);

    IEEntity entity = ecs->create();
    int nameIndex = nameSystem->lookUpIndex(entity);
    nameSystem->setName(nameIndex, "Test_" + QString::number(row + col));

    int index = ecs->attachComponent(entity, IEComponentType::Renderable);
    renderableSystem->setRenderableId(index, id);
    renderableSystem->addShown(index);

    int indexTransform = transformSystem->lookUpIndex(entity);
    transformSystem->setPosition(indexTransform, QVector3D((float)row * 2.0f, (float)value * 2.0f, (float)col * 2.0f));

    auto scene = game->getIEScene();
    auto renderable = scene->getRenderableManager()->getValue(id);
    renderable->appendMat4InstanceValue("aModel", QMatrix4x4());
}
