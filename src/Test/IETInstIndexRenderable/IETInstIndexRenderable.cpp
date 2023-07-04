#include "IETInstIndexRenderable.h"
#include "IEMesh.h"
#include "IEShader.h"
#include "IEMaterial.h"
#include "IEInstIndexRenderable.h"
#include "IEIndexBufferObject.h"
#include "IEVertexBufferObject.h"
#include "IEShaderImport.h"
#include "IEMeshImport.h"
#include "IECamera.h"
#include "IEBufferObjectFactory.h"

IETInstIndexRenderable::IETInstIndexRenderable() :
    QWidget(),
    mesh(nullptr), material(nullptr),
    shader(nullptr), renderable(nullptr)
{
    mesh = new IEMesh("./resources/root/Content/suzanne.obj", this);
    material = new IEMaterial("", this);
    shader = new IEShader("./resources/shaders/tests/instanced_renderable.glsl", this);

    IEMeshImport::importMesh(mesh->getName(), *mesh, *material);
    IEShaderImport::importShader(shader->getName(), *shader);

    renderable = new IEInstIndexRenderable("", material->getId(), shader->getId(), this);
    process(mesh, renderable);
    renderable->build(*shader);
    renderable->addShown();

    this->show();
}

IETInstIndexRenderable::~IETInstIndexRenderable()
{

}

void IETInstIndexRenderable::draw(IECamera* camera)
{
    shader->bind();
    shader->setUniformValue("uViewProjection", camera->getViewProjection());

    for(int i = 0; i < renderable->getVaoSize(); i++)
    {
        renderable->draw(i);
    }
}

void IETInstIndexRenderable::process(IEMesh* mesh, IEInstIndexRenderable* renderable)
{
    auto& meshes = mesh->getMeshes();
    for(int i = 0; i < meshes.size(); i++)
    {
        int index = renderable->addVAO();
        renderable->addIBO(new IEIndexBufferObject(meshes[i]->getIndices(), renderable));
        renderable->addBuffer(index, "aPos", IEBufferObjectFactory::make(IEBufferType::Vec3, 3, 0, 0, 0, renderable));
        renderable->addBuffer(index, "aNormal", IEBufferObjectFactory::make(IEBufferType::Vec3, 3, 0, 0, 0, renderable));
        renderable->addBuffer(index, "aTangent", IEBufferObjectFactory::make(IEBufferType::Vec3, 3, 0, 0, 0, renderable));
        renderable->addBuffer(index, "aBitangent", IEBufferObjectFactory::make(IEBufferType::Vec3, 3, 0, 0, 0, renderable));
        renderable->addBuffer(index, "aTexCoord", IEBufferObjectFactory::make(IEBufferType::Vec2, 3, 0, 0, 0, renderable));
        renderable->addBuffer(index, "aModel", IEBufferObjectFactory::make(IEBufferType::Mat4, 4, 68, 16, 4, renderable));

        renderable->setBufferValues("aPos", meshes[i]->getPosVertices());
        renderable->setBufferValues("aNormal", meshes[i]->getNormVertices());
        renderable->setBufferValues("aTangent", meshes[i]->getTanVertices());
        renderable->setBufferValues("aBitangent", meshes[i]->getBiTanVertices());
        renderable->setBufferValues("aTexCoord", meshes[i]->getTexVertices());
    }

    auto& children = mesh->getChildren();
    for(int i = 0; i < children.size(); i++)
    {
        process(children[i], renderable);
    }
}

