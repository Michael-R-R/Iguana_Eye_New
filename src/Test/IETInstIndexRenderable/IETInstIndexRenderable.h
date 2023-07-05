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

    IEMesh* mesh;
    IEMaterial* material;
    IEShader* shader;
    IEInstIndexRenderable* renderable;

    QString meshPath;
    QString materialPath;
    QString shaderPath;
    int createCount;
    int showCount;
    int hideCount;

public:
    IETInstIndexRenderable();
    virtual ~IETInstIndexRenderable();

    void draw(IECamera* camera);

private:
    void setup();
    void createResources();
    void appendShown();
    void showInstances();
    void hideInstances();
    void serialize();
    void deserialize();
};

