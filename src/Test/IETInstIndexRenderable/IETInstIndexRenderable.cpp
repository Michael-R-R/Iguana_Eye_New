#include "IETInstIndexRenderable.h"
#include "IEMesh.h"
#include "IEShader.h"
#include "IEMaterial.h"
#include "IEInstIndexRenderable.h"
#include "IEIndexBufferObject.h"
#include "IEVertexBufferObject.h"
#include "IEGlslImport.h"
#include "IEMeshImport.h"
#include "IECamera.h"
#include "IEBufferObjectFactory.h"
#include "ApplicationWindow.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEECS.h"
#include "IEECSTransformSystem.h"
#include "IEECSRenderableSystem.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"
#include "IESerialize.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QOpenGLContext>

IETInstIndexRenderable::IETInstIndexRenderable() :
    QWidget(),
    vLayout(new QVBoxLayout(this)),
    renderable(nullptr),
    meshPath("./resources/root/Content/cube/cube.obj"),
    shaderPath("./resources/root/Content/default.glsl"),
    createCount(10),
    removeCount(1),
    showCount(1),
    hideCount(1)
{
    this->setup();
    this->show();
}

IETInstIndexRenderable::~IETInstIndexRenderable()
{

}

void IETInstIndexRenderable::setup()
{
    this->setAttribute(Qt::WA_QuitOnClose, false);

    auto* meLineEdit = new QLineEdit(meshPath, this);
    auto* sLineEdit = new QLineEdit(shaderPath, this);
    vLayout->addWidget(meLineEdit);
    vLayout->addWidget(sLineEdit);
    connect(meLineEdit, &QLineEdit::textChanged, this, [this](const QString& path){ meshPath = path; });
    connect(sLineEdit, &QLineEdit::textChanged, this, [this](const QString& path){ shaderPath = path; });

    auto* createResourcesButton = new QPushButton("Create Resources", this);
    vLayout->addWidget(createResourcesButton);
    connect(createResourcesButton, &QPushButton::clicked, this, [this](){ createResources(); });

    auto* createCountSpinbox = new QSpinBox(this);
    auto* createEntityButton = new QPushButton("Create Entity", this);
    vLayout->addWidget(createCountSpinbox);
    vLayout->addWidget(createEntityButton);
    createCountSpinbox->setValue(createCount);
    createCountSpinbox->setMinimum(1);
    createCountSpinbox->setMaximum(50000);
    connect(createCountSpinbox, &QSpinBox::valueChanged, this, [this](int val){ createCount = val; });
    connect(createEntityButton, &QPushButton::clicked, this, [this](){ createEntity(); });

    auto* removeCountSpinbox = new QSpinBox(this);
    auto* removeEntityButton = new QPushButton("Remove Entity", this);
    vLayout->addWidget(removeCountSpinbox);
    vLayout->addWidget(removeEntityButton);
    removeCountSpinbox->setValue(removeCount);
    removeCountSpinbox->setMinimum(1);
    removeCountSpinbox->setMaximum(50000);
    connect(removeCountSpinbox, &QSpinBox::valueChanged, this, [this](int val){ removeCount = val; });
    connect(removeEntityButton, &QPushButton::clicked, this, [this](){ removeEntity(); });

    auto* showCountSpinbox = new QSpinBox(this);
    auto* showButton = new QPushButton("Show", this);
    vLayout->addWidget(showCountSpinbox);
    vLayout->addWidget(showButton);
    showCountSpinbox->setValue(showCount);
    showCountSpinbox->setMinimum(1);
    showCountSpinbox->setMaximum(50000);
    connect(showCountSpinbox, &QSpinBox::valueChanged, this, [this](int val){ showCount = val; });
    connect(showButton, &QPushButton::clicked, this, [this](){ showInstances(); });

    auto* hideCountSpinbox = new QSpinBox(this);
    auto* hideButton = new QPushButton("Hide", this);
    vLayout->addWidget(hideCountSpinbox);
    vLayout->addWidget(hideButton);
    hideCountSpinbox->setValue(hideCount);
    hideCountSpinbox->setMinimum(1);
    hideCountSpinbox->setMaximum(50000);
    connect(hideCountSpinbox, &QSpinBox::valueChanged, this, [this](int val){ hideCount = val; });
    connect(hideButton, &QPushButton::clicked, this, [this](){ hideInstances(); });

    auto* serializeButton = new QPushButton("Serialize", this);
    auto* deserializeButton = new QPushButton("Deserialize", this);
    vLayout->addWidget(serializeButton);
    vLayout->addWidget(deserializeButton);
    connect(serializeButton, &QPushButton::clicked, this, [this](){ serialize(); });
    connect(deserializeButton, &QPushButton::clicked, this, [this](){ deserialize(); });
}

void IETInstIndexRenderable::createResources()
{
    auto* game = ApplicationWindow::instance().getGame();
    auto* scene = game->getSystem<IEScene>();
    auto* meManger = scene->getManager<IEMeshManager>();
    auto* maManger = scene->getManager<IEMaterialManager>();
    auto* sManger = scene->getManager<IEShaderManager>();
    auto* rManger = scene->getManager<IERenderableManager>();

    game->makeCurrent();

    clearManagers();

    auto* mesh = new IEMesh(this);
    auto* material = new IEMaterial(this);
    auto* shader = new IEShader(this);
    renderable = new IEInstIndexRenderable(this);

    IEGlslImport::importPath(shaderPath, *shader);
    IEMeshImport::importPath(meshPath, *mesh, *material, *shader, *renderable);

    const int nodeCount = renderable->getNodes().size();
    for(int i = 0; i < nodeCount; i++)
    {
        renderable->getInstIndexNode(i)->IBO->setValues(mesh->getNode(i)->indices);
        renderable->addBuffer(i, "aModel", IEBufferType::Mat4, 64, 16, 4);
        renderable->build(i, *shader);
    }

    meManger->add(mesh->getID(), mesh);
    maManger->add(material->getID(), material);
    sManger->add(shader->getID(), shader);
    rManger->add(renderable->getID(), renderable);
}

void IETInstIndexRenderable::createEntity()
{
    if(!renderable)
        return;

    auto* game = ApplicationWindow::instance().getGame();
    auto* ecs = game->getSystem<IEECS>();
    auto* tSystem = ecs->getComponent<IEECSTransformSystem>();
    auto* rSystem = ecs->getComponent<IEECSRenderableSystem>();
    int count = ecs->entityCount();

    for(int i = count; i < count + createCount; i++)
    {
        IEEntity entity = ecs->create();

        int rIndex = ecs->attachComponent<IEECSRenderableSystem>(entity);
        rSystem->setResourceId(rIndex, renderable->getID());
        rSystem->showInstance(rIndex);

        int tIndex = tSystem->lookUpIndex(entity);
        tSystem->setPosition(tIndex, glm::vec3(i * 2.5f, 0.0f, 0.0f));
    }
}

void IETInstIndexRenderable::removeEntity()
{
    auto* game = ApplicationWindow::instance().getGame();
    auto* ecs = game->getSystem<IEECS>();

    int i = 0;
    while(ecs->entityCount() > 0)
    {
        ecs->remove(IEEntity(i++));
    }
}

void IETInstIndexRenderable::showInstances()
{
    auto* game = ApplicationWindow::instance().getGame();
    auto* ecs = game->getSystem<IEECS>();
    auto* rSystem = ecs->getComponent<IEECSRenderableSystem>();

    for(int i = 1; i < 100; i++)
    {
        if((i % showCount) != 0)
            continue;

        const int index = rSystem->lookUpIndex(IEEntity(i));

        rSystem->showInstance(index);
    }
}

void IETInstIndexRenderable::hideInstances()
{
    auto* game = ApplicationWindow::instance().getGame();
    auto* ecs = game->getSystem<IEECS>();
    auto* rSystem = ecs->getComponent<IEECSRenderableSystem>();

    for(int i = 1; i < 100; i++)
    {
        if((i % hideCount) != 0)
            continue;

        const int index = rSystem->lookUpIndex(IEEntity(i));

        rSystem->hideInstance(index);
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
    if(!renderable)
        return;

    auto* game = ApplicationWindow::instance().getGame();
    auto* scene = game->getSystem<IEScene>();
    auto* sManger = scene->getManager<IEShaderManager>();
    auto* rManger = scene->getManager<IERenderableManager>();

    game->makeCurrent();

    QString path = renderable->getName();

    rManger->remove(renderable->getID());
    renderable = new IEInstIndexRenderable(this);
    IESerialize::read<IEInstIndexRenderable>(path, renderable);

    auto* shader = sManger->value<IEShader>(renderable->getShaderID());
    const int nodeCount = renderable->getNodes().size();
    for(int i = 0; i < nodeCount; i++)
    {
        renderable->build(i, *shader);
    }

    rManger->add(renderable->getID(), renderable);
}

void IETInstIndexRenderable::clearManagers()
{
    auto* game = ApplicationWindow::instance().getGame();
    auto* scene = game->getSystem<IEScene>();
    auto* meManger = scene->getManager<IEMeshManager>();
    auto* maManger = scene->getManager<IEMaterialManager>();
    auto* sManger = scene->getManager<IEShaderManager>();
    auto* rManger = scene->getManager<IERenderableManager>();

    meManger->cleanup();
    maManger->cleanup();
    sManger->cleanup();
    rManger->cleanup();
}


