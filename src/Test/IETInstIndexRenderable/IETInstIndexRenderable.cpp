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
#include "ApplicationWindow.h"
#include "IEGame.h"
#include <QLineEdit>
#include <QPushButton>
#include <QOpenGLContext>

IETInstIndexRenderable::IETInstIndexRenderable() :
    QWidget(),
    vLayout(new QVBoxLayout(this)),
    mesh(nullptr), material(nullptr),
    shader(nullptr), renderable(nullptr),
    meshPath("./resources/root/Content/cube/cube.obj"),
    shaderPath("./resources/shaders/tests/instanced_renderable.glsl")
{
    this->setup();
    this->show();
}

IETInstIndexRenderable::~IETInstIndexRenderable()
{

}

void IETInstIndexRenderable::draw(IECamera* camera)
{
    if(!mesh || !material || !shader || !renderable)
        return;

    shader->bind();
    shader->setUniformValue("uViewProjection", camera->getViewProjection());

    auto& maChildren = material->getChildren();
    auto& rChildren = renderable->getChildren();
    for(int i = 0; i < rChildren.size(); i++)
    {
        auto& materials = maChildren[i]->getMaterials();
        auto& renderables = rChildren[i]->getRenderables();
        for(int j = 0; j < renderables.size(); j++)
        {
            materials[j]->bindColors(*shader);
            renderables[j]->draw();
        }
    }
}

void IETInstIndexRenderable::setup()
{
    this->setWindowFlag(Qt::WindowStaysOnTopHint, true);
    this->setAttribute(Qt::WA_QuitOnClose, false);

    auto* meLineEdit = new QLineEdit(meshPath, this);
    auto* sLineEdit = new QLineEdit(shaderPath, this);
    auto* createButton = new QPushButton("Create", this);
    auto* addShownButton = new QPushButton("Add Shown", this);

    vLayout->addWidget(meLineEdit);
    vLayout->addWidget(sLineEdit);
    vLayout->addWidget(createButton);
    vLayout->addWidget(addShownButton);

    connect(meLineEdit, &QLineEdit::textChanged, this, [this](const QString& path){ meshPath = path; });
    connect(sLineEdit, &QLineEdit::textChanged, this, [this](const QString& path){ shaderPath = path; });
    connect(createButton, &QPushButton::clicked, this, [this](){ createResources(); });
    connect(addShownButton, &QPushButton::clicked, this, [this](){ addShown(); });
}

void IETInstIndexRenderable::createResources()
{
    ApplicationWindow::instance().getGame()->makeCurrent();

    delete mesh;
    delete material;
    delete shader;
    delete renderable;

    mesh = new IEMesh(meshPath, this);
    material = new IEMaterial("./resources/root/Content/test.iemat", this);
    shader = new IEShader(shaderPath, this);

    IEMeshImport::importMesh(mesh->getName(), *mesh, *material);
    IEShaderImport::importShader(shader->getName(), *shader);

    renderable = new IEInstIndexRenderable("", mesh->getId(), material->getId(), shader->getId(), this);
    processNode(shader, mesh, renderable);
}

void IETInstIndexRenderable::processNode(IEShader* shader, IEMesh* mesh, IEInstIndexRenderable* ieRenderable)
{
    auto& meshes = mesh->getMeshes();
    for(int i = 0; i < meshes.size(); i++)
    {
        auto* renderable = new IEInstIndexRenderable(ieRenderable);
        processRenderable(shader, meshes[i], renderable);
        ieRenderable->getRenderables().append(renderable);
    }

    auto& children = mesh->getChildren();
    for(int i = 0; i < children.size(); i++)
    {
        auto* child = new IEInstIndexRenderable(ieRenderable);
        processNode(shader, children[i], child);
        ieRenderable->getChildren().append(child);
    }
}

void IETInstIndexRenderable::processRenderable(IEShader* shader, IEMesh* mesh, IEInstIndexRenderable* renderable)
{
    renderable->init();
    renderable->addIBO(new IEIndexBufferObject(mesh->getIndices(), renderable));
    renderable->addBuffer("aPos", IEBufferObjectFactory::make(IEBufferType::Vec3, 3, 0, 0, 0, renderable));
    renderable->addBuffer("aNormal", IEBufferObjectFactory::make(IEBufferType::Vec3, 3, 0, 0, 0, renderable));
    renderable->addBuffer("aTangent", IEBufferObjectFactory::make(IEBufferType::Vec3, 3, 0, 0, 0, renderable));
    renderable->addBuffer("aBitangent", IEBufferObjectFactory::make(IEBufferType::Vec3, 3, 0, 0, 0, renderable));
    renderable->addBuffer("aTexCoord", IEBufferObjectFactory::make(IEBufferType::Vec2, 3, 0, 0, 0, renderable));
    renderable->addBuffer("aModel", IEBufferObjectFactory::make(IEBufferType::Mat4, 4, 68, 16, 4, renderable));

    renderable->setBufferValues("aPos", mesh->getPosVertices());
    renderable->setBufferValues("aNormal", mesh->getNormVertices());
    renderable->setBufferValues("aTangent", mesh->getTanVertices());
    renderable->setBufferValues("aBitangent", mesh->getBiTanVertices());
    renderable->setBufferValues("aTexCoord", mesh->getTexVertices());

    renderable->build(*shader);
}

void IETInstIndexRenderable::addShown()
{
    foreach(auto* child, renderable->getChildren())
    {
        foreach(auto* i, child->getRenderables())
        {
            auto* temp = static_cast<IEInstIndexRenderable*>(i);

            int index = temp->addShown();

            QMatrix4x4 model;
            model.translate(index * 2.5f, 0.0f, 0.0f);

            temp->setBufferValue("aModel", index, model);
        }
    }
}

