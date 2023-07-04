#pragma once

#include <QWidget>

class IEMesh;
class IEMaterial;
class IEShader;
class IEInstIndexRenderable;
class IECamera;

class IETInstIndexRenderable : public QWidget
{
    IEMesh* mesh;
    IEMaterial* material;
    IEShader* shader;
    IEInstIndexRenderable* renderable;

public:
    IETInstIndexRenderable();
    virtual ~IETInstIndexRenderable();

    void draw(IECamera* camera);

private:
    void process(IEMesh* mesh, IEInstIndexRenderable* renderable);
};

