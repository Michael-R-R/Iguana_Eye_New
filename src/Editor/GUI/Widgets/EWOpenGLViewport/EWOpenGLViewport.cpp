#include "EWOpenGLViewport.h"
#include "RenderEngineStartEvent.h"

EWOpenGLViewport::EWOpenGLViewport(const QString title, QWidget* parent) :
    QOpenGLWidget(parent),
    format(new QSurfaceFormat()),
    glFunc(nullptr), glExtraFunc(nullptr),
    time(new EWOpenGLViewportTime(33, 33, this)),
    input(new EWOpenGLViewportInput(this, this)),
    renderEngine(new IERenderEngine(this)),
    meshManager(new IEMeshManager(this)), materialManager(new IEMaterialManager(this)),
    shaderManager(new IEShaderManager(this)), renderableManager(new IERenderableManager(this))
{
    this->setWindowTitle(title);
    format->setVersion(4, 3);
    format->setProfile(QSurfaceFormat::CoreProfile);
    format->setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format->setSwapInterval(1);
    format->setSamples(16);
    this->setFormat(*format); // must be set before window is shown
}

EWOpenGLViewport::~EWOpenGLViewport()
{
    this->shutdown();
}

void EWOpenGLViewport::startup()
{
    RenderEngineStartEvent renderStartEvent(meshManager, materialManager,
                                            shaderManager, renderableManager);

    renderEngine->startup(renderStartEvent);
    time->startup(this);
}

void EWOpenGLViewport::shutdown()
{
    time->shutdown();
    renderEngine->shutdown();
    meshManager->shutdown();
    materialManager->shutdown();
    shaderManager->shutdown();
    renderableManager->shutdown();
}

void EWOpenGLViewport::addRenderableCopy(const IEMesh* mesh, const IEMaterial* material,
                                   const IEShader* shader, const IERenderable* renderable)
{
    if(!mesh || !material || !shader || !renderable)
        return;

    this->makeCurrent();

    auto meshId = mesh->getId();
    auto meshCopy = new IEMesh(*mesh);
    meshCopy->setId(meshId);
    meshManager->add(meshId, meshCopy);

    auto materialId = material->getId();
    auto materialCopy = new IEMaterial(*material);
    materialCopy->setId(materialId);
    materialManager->add(materialId, materialCopy);

    auto shaderId = shader->getId();
    auto shaderCopy = new IEShader(*shader);
    shaderCopy->setId(shaderId);
    shaderCopy->build();
    shaderManager->add(shaderId, shaderCopy);

    auto renderableId = renderable->getId();
    auto renderableCopy = new IERenderable(*renderable);
    renderableCopy->setId(renderableId);
    renderableCopy->setMeshId(meshId);
    renderableCopy->setMaterialId(materialId);
    renderableCopy->setShaderId(shaderId);
    renderableCopy->build(shaderCopy);
    renderableManager->add(renderableId, renderableCopy);

    this->doneCurrent();
}

void EWOpenGLViewport::onUpdateFrame()
{

}

void EWOpenGLViewport::onRenderFrame()
{
    glExtraFunc->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderEngine->onRenderFrame();

    time->processDeltaTime();
}

void EWOpenGLViewport::initializeGL()
{
    glFunc = QOpenGLContext::currentContext()->functions();
    glExtraFunc = QOpenGLContext::currentContext()->extraFunctions();

    glFunc->initializeOpenGLFunctions();
    glExtraFunc->initializeOpenGLFunctions();

    glExtraFunc->glEnable(GL_MULTISAMPLE);
    glExtraFunc->glEnable(GL_DEPTH_TEST);

    glExtraFunc->glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

    emit initialized();
}

void EWOpenGLViewport::resizeGL(int w, int h)
{
    glFunc->glViewport(0, 0, w, h);
}

void EWOpenGLViewport::paintGL()
{
    this->onRenderFrame();
}
