#include "EWOpenGLViewport.h"

EWOpenGLViewport::EWOpenGLViewport(const QString title, QWidget* parent) :
    QOpenGLWidget(parent),
    format(new QSurfaceFormat()),
    glFunc(nullptr), glExtraFunc(nullptr),
    time(new EWOpenGLViewportTime(33, 33, this)),
    input(new EWOpenGLViewportInput(this, this))
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
    time->startup(this);
}

void EWOpenGLViewport::shutdown()
{
    time->shutdown();
}

void EWOpenGLViewport::onUpdateFrame()
{

}

void EWOpenGLViewport::onRenderFrame()
{
    glExtraFunc->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
