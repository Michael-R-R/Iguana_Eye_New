#include "GLViewport.h"
#include "RenderEngineStartEvent.h"

GLViewport::GLViewport(const QString title, QWidget* parent) :
    QOpenGLWidget(parent),
    format(new QSurfaceFormat()),
    glFunc(nullptr), glExtraFunc(nullptr),
    time(new GLTime(33, 33, this)),
    input(new GLInput(this, this)),
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

GLViewport::~GLViewport()
{
    this->shutdown();
}

void GLViewport::startup()
{
    RenderEngineStartEvent renderStartEvent(meshManager, materialManager,
                                            shaderManager, renderableManager);

    renderEngine->startup(renderStartEvent);
    time->startup(this);
}

void GLViewport::shutdown()
{
    time->shutdown();
}

void GLViewport::onUpdateFrame()
{

}

void GLViewport::onRenderFrame()
{
    glExtraFunc->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderEngine->onRenderFrame();

    time->processDeltaTime();
}

void GLViewport::initializeGL()
{
    glFunc = QOpenGLContext::currentContext()->functions();
    glExtraFunc = QOpenGLContext::currentContext()->extraFunctions();

    glFunc->initializeOpenGLFunctions();
    glExtraFunc->initializeOpenGLFunctions();

    glExtraFunc->glEnable(GL_MULTISAMPLE);
    glExtraFunc->glEnable(GL_DEPTH_TEST);

    glExtraFunc->glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
}

void GLViewport::resizeGL(int w, int h)
{
    glFunc->glViewport(0, 0, w, h);
}

void GLViewport::paintGL()
{
    this->onRenderFrame();
}
