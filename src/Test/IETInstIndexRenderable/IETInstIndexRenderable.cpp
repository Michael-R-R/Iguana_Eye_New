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
#include "IESerialize.h"
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QOpenGLContext>

IETInstIndexRenderable::IETInstIndexRenderable() :
    QWidget(),
    vLayout(new QVBoxLayout(this)),
    mesh(nullptr), material(nullptr),
    shader(nullptr), renderable(nullptr),
    meshPath("./resources/root/Content/cube/cube.obj"),
    materialPath("./resources/root/Content/material.iemat"),
    shaderPath("./resources/shaders/tests/instanced_renderable.glsl"),
    createCount(1),
    showCount(0),
    hideCount(0)
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
    auto* createCountSpinbox = new QSpinBox(this);
    auto* addShownButton = new QPushButton("Add", this);
    auto* showCountSpinbox = new QSpinBox(this);
    auto* showButton = new QPushButton("Show", this);
    auto* hideCountSpinbox = new QSpinBox(this);
    auto* hideButton = new QPushButton("Hide", this);
    auto* serializeButton = new QPushButton("Serialize", this);
    auto* deserializeButton = new QPushButton("Deserialize", this);

    createCountSpinbox->setMaximum(50000);

    vLayout->addWidget(meLineEdit);
    vLayout->addWidget(sLineEdit);
    vLayout->addWidget(createButton);
    vLayout->addWidget(createCountSpinbox);
    vLayout->addWidget(addShownButton);
    vLayout->addWidget(showCountSpinbox);
    vLayout->addWidget(showButton);
    vLayout->addWidget(hideCountSpinbox);
    vLayout->addWidget(hideButton);
    vLayout->addWidget(serializeButton);
    vLayout->addWidget(deserializeButton);

    connect(meLineEdit, &QLineEdit::textChanged, this, [this](const QString& path){ meshPath = path; });
    connect(sLineEdit, &QLineEdit::textChanged, this, [this](const QString& path){ shaderPath = path; });
    connect(createButton, &QPushButton::clicked, this, [this](){ createResources(); });
    connect(addShownButton, &QPushButton::clicked, this, [this](){ appendShown(); });
    connect(createCountSpinbox, &QSpinBox::valueChanged, this, [this](int val){ createCount = val; });
    connect(showCountSpinbox, &QSpinBox::valueChanged, this, [this](int val){ showCount = val; });
    connect(hideCountSpinbox, &QSpinBox::valueChanged, this, [this](int val){ hideCount = val; });
    connect(showButton, &QPushButton::clicked, this, [this](){ showInstances(); });
    connect(hideButton, &QPushButton::clicked, this, [this](){ hideInstances(); });
    connect(serializeButton, &QPushButton::clicked, this, [this](){ serialize(); });
    connect(deserializeButton, &QPushButton::clicked, this, [this](){ deserialize(); });
}

void IETInstIndexRenderable::createResources()
{
    ApplicationWindow::instance().getGame()->makeCurrent();

    delete mesh;
    delete material;
    delete shader;
    delete renderable;

    mesh = new IEMesh(meshPath, this);
    material = new IEMaterial(materialPath, this);
    shader = new IEShader(shaderPath, this);
    renderable = new IEInstIndexRenderable(this);

    IEMeshImport::importMesh(mesh->getName(), *mesh, *material, *shader, *renderable);
    IEShaderImport::importShader(shader->getName(), *shader);

    auto& meChildren = mesh->getChildren();
    auto& rChildren = renderable->getChildren();
    for(int i = 0; i < rChildren.size(); i++)
    {
        auto& meshes = meChildren[i]->getMeshes();
        auto& renderables = rChildren[i]->getRenderables();
        for(int j = 0; j < renderables.size(); j++)
        {
            auto* temp = static_cast<IEInstIndexRenderable*>(renderables[j]);
            temp->addIBO(new IEIndexBufferObject(meshes[j]->getIndices(), temp));
            temp->addBuffer("aModel", IEBufferObjectFactory::make(IEBufferType::Mat4, 4, 68, 16, 4, temp));
            temp->build(*shader);
        }
    }
}

void IETInstIndexRenderable::appendShown()
{
    foreach(auto* child, renderable->getChildren())
    {
        foreach(auto* i, child->getRenderables())
        {
            for(int j = 0; j < createCount; j++)
            {
                auto* temp = static_cast<IEInstIndexRenderable*>(i);

                int index = temp->addShown();

                QMatrix4x4 model;
                model.translate(index * 2.5f, 0.0f, 0.0f);

                temp->setBufferValue("aModel", index, model);
            }
        }
    }
}

void IETInstIndexRenderable::showInstances()
{
    auto& rChildren = renderable->getChildren();
    for(int i = 0; i < rChildren.size(); i++)
    {
        auto& renderables = rChildren[i]->getRenderables();
        for(int j = 0; j < renderables.size(); j++)
        {
            auto* temp = static_cast<IEInstRenderable*>(renderables[j]);
            const int hidden = temp->getHiddenCount();
            for(int k = hidden - 1; k > -1; k-=(showCount + 1))
            {
                temp->addShown(k);
            }
        }
    }
}

void IETInstIndexRenderable::hideInstances()
{
    auto& rChildren = renderable->getChildren();
    for(int i = 0; i < rChildren.size(); i++)
    {
        auto& renderables = rChildren[i]->getRenderables();
        for(int j = 0; j < renderables.size(); j++)
        {
            auto* temp = static_cast<IEInstRenderable*>(renderables[j]);
            const int shown = temp->getShownCount();
            for(int k = shown - 1; k > -1; k-=(hideCount + 1))
            {
                temp->addHidden(k);
            }
        }
    }
}

void IETInstIndexRenderable::serialize()
{
    if(!renderable)
        return;

    IESerialize::write<IERenderable>(renderable->getName(), renderable);
}

void IETInstIndexRenderable::deserialize()
{
    QString path = "";

    if(renderable)
    {
        path = renderable->getName();
        delete renderable;
    }

    ApplicationWindow::instance().getGame()->makeCurrent();

    renderable = new IEInstIndexRenderable(this);
    IESerialize::read<IEInstIndexRenderable>(path, renderable);

    foreach(auto* child, renderable->getChildren())
    {
        foreach(auto* i, child->getRenderables())
        {
            i->build(*shader);
        }
    }
}


