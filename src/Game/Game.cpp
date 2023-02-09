#include "Game.h"
#include "GameStartEvent.h"

Game::Game(QWidget* parent) :
    QOpenGLWidget(parent),
    format(new QSurfaceFormat()),
    glFunc(nullptr), glExtraFunc(nullptr),
    time(new IETime(8, 16, this)),
    input(new IEInput(this, this)),
    scene(new IEScene(this))
{
    format->setVersion(4, 3);
    format->setProfile(QSurfaceFormat::CoreProfile);
    format->setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format->setSwapInterval(1);
    format->setSamples(16);
    this->setFormat(*format); // must be set before window is shown
}

Game::~Game()
{

}

void Game::startup()
{
    this->makeCurrent();

    GameStartEvent event(time, input, scene);

    scene->startup(event);
    time->startup(this);

    this->setFocus();
}

void Game::shutdown()
{
    this->makeCurrent();

    time->shutdown();
    scene->shutdown();

    delete time;
    delete input;
    delete scene;
}

void Game::onUpdateFrame()
{

}

void Game::onRenderFrame()
{
    glExtraFunc->glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glExtraFunc->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // TODO test

    auto shader = scene->getShaderManager()->getValue(1);
    auto renderable = scene->getRenderableManager()->getValue(2);
    if(shader && renderable)
    {
        shader->bind();
        renderable->bind();
        glExtraFunc->glDrawArrays(GL_TRIANGLES, 0, 3);
        shader->release();
        renderable->release();
    }

    // -----

    time->processDeltaTime();
}

void Game::initializeGL()
{
    glFunc = QOpenGLContext::currentContext()->functions();
    glExtraFunc = QOpenGLContext::currentContext()->extraFunctions();

    glFunc->initializeOpenGLFunctions();
    glExtraFunc->initializeOpenGLFunctions();

    glExtraFunc->glEnable(GL_MULTISAMPLE);
    glExtraFunc->glEnable(GL_DEPTH_TEST);

    // TODO test
    QVector<QVector3D> vertices =
    {
        QVector3D(0.0f, 0.5f, 0.0f),
        QVector3D(0.5f, 0.0f, 0.0f),
        QVector3D(-0.5f, 0.0f, 0.0f)
    };

    auto shader = new IEShader(1, "./resources/shaders/Test.glsl");
    shader->build();
    scene->getShaderManager()->add(1, shader);

    auto buffer = new IEBuffer<QVector3D>(QOpenGLBuffer::VertexBuffer);
    buffer->initData(vertices, 3, 0, 0);

    auto renderable = new IERenderable(2);
    renderable->getVec3BufferContainer()->add("aPos", buffer);
    renderable->build(shader);
    scene->getRenderableManager()->add(2, renderable);

    // --------------------

    emit initialized();
}

void Game::paintGL()
{
    onRenderFrame();
}

void Game::resizeGL(int w, int h)
{
    glFunc->glViewport(0, 0, w, h);
}
