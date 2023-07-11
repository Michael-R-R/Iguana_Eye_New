#pragma once

#include <QWidget>
#include <QVBoxLayout>

class IEMesh;
class IEMaterial;
class IEShader;
class IEInstIndexRenderable;
class IECamera;

class IETInstIndexRenderable : public QWidget
{
    QVBoxLayout* vLayout;

    IEInstIndexRenderable* renderable;

    QString meshPath;
    QString shaderPath;
    int createCount;
    int removeCount;
    int showCount;
    int hideCount;

public:
    IETInstIndexRenderable();
    virtual ~IETInstIndexRenderable();

private:
    void setup();
    void createResources();
    void createEntity();
    void removeEntity();
    void showInstances();
    void hideInstances();
    void serialize();
    void deserialize();
    void clearManagers();
};

