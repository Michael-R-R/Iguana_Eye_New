#pragma once

#include <QVector>
#include <QPair>

#include "IERandomNumber.h"

class IEGame;
class IEScene;
class IEMesh;
class IEShader;

class IETIslandGenerator
{
    struct Particle
    {
        int currXLoc, currYLoc, lifeTime;

        Particle() :
            currXLoc(0), currYLoc(0), lifeTime(0) {}
    };

    struct World
    {
        int width, height;
        int waterline, landZone;
        int particleAmount;

        QVector<QVector<int>> valueArray;
        QVector<Particle> particleArray;

        World() :
            width(0), height(0), waterline(0), landZone(0),
            particleAmount(0), valueArray(), particleArray() {}
    };

    struct DropZone
    {
        int centerX, centerY, radius;
        int xDropLoc, yDropLoc;

        DropZone() :
            centerX(0), centerY(0), radius(0),
            xDropLoc(0), yDropLoc(0) {}
    };

    unsigned long long deepWaterId = 0;
    unsigned long long shallowWaterId = 0;
    unsigned long long sandId = 0;
    unsigned long long grassId = 0;
    unsigned long long forestId = 0;
    unsigned long long mountainId = 0;

    World world;
    DropZone dropZone;
    Particle particle;
    int buildRow = 0;
    int buildCol = 0;

public:
    IETIslandGenerator(IEGame* game);
    ~IETIslandGenerator() {}

    void run(IEGame* game);

private:
    void buildDeepWaterRenderable(IEMesh* mesh, IEShader* shader, IEScene* scene);
    void buildShallowWaterRenderable(IEMesh* mesh, IEShader* shader, IEScene* scene);
    void buildSandRenderable(IEMesh* mesh, IEShader* shader, IEScene* scene);
    void buildGrassRenderable(IEMesh* mesh, IEShader* shader, IEScene* scene);
    void buildForestRenderable(IEMesh* mesh, IEShader* shader, IEScene* scene);
    void buildMountainRenderable(IEMesh* mesh, IEShader* shader, IEScene* scene);

    void setupParameters();
    void setupWorld();
    void calcDropZone(int w, int h);
    void generateWorld();
    QPair<int, int> getParticleLoc(const Particle& particle);
    void checkIfValidMove(QVector<QPair<int, int>>& validMoves, int xLoc, int yLoc, int currIndexVal);
    void normalizeValues();
    int findMaxValue();
    void translateWorld(IEGame* game);
    void printWorld();

    void createDeepWaterEntity(const int row, const int col, IEGame* game);
    void createShallowWaterEntity(const int row, const int col, IEGame* game);
    void createSandEntity(const int row, const int col, IEGame* game);
    void createGrassEntity(const int row, const int col, IEGame* game);
    void createForestEntity(const int row, const int col, IEGame* game);
    void createMountainEntity(const int row, const int col, IEGame* game);
    void createEntity(const int row, const int col, const int value,
                      const unsigned long long id, IEGame* game);
};

