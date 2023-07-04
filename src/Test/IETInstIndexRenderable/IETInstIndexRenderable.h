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
    QString shaderPath;

public:
    IETInstIndexRenderable();
    virtual ~IETInstIndexRenderable();

    void draw(IECamera* camera);

private:
    void setup();
    void createResources();
    void processNode(IEShader* shader, IEMesh* mesh, IEInstIndexRenderable* renderable);
    void processRenderable(IEShader* shader, IEMesh* mesh, IEInstIndexRenderable* renderable);
    void addShown();
};

