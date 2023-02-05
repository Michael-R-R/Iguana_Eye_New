#include "Game.h"

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
    scene->startup();
    time->startup(this);
    this->setFocus();
}

void Game::shutdown()
{
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

    shader->bind();
    vao->bind();
    material->bindUniformData(shader);
    glExtraFunc->glDrawArrays(GL_TRIANGLES, 0, mesh->getPosVertices().size());
    vao->release();
    shader->release();

    // -------------------------

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
        QVector3D(0.5f, 0.5f, 0.0f),
        QVector3D(0.5f, -0.5f, 0.0f),
        QVector3D(-0.5f, -0.5f, 0.0f),
        QVector3D(-0.5f, 0.5f, 0.0f)
    };

    vao = new QOpenGLVertexArrayObject();
    buffer = new IEBuffer();
    mesh = new IEMesh(1);
    material = new IEMaterial(2);
    shader = new IEShader(3, "./resources/shaders/Test.glsl");

    mesh->setPosVertices(vertices);
    auto uniform = material->getUniformData();
    uniform.add("uColor", QColor(99, 130, 82, 255));
    material->setUniformData(uniform);

    shader->create();
    shader->addShaderFromSourceCode(QOpenGLShader::Vertex, shader->getVertexSrc());
    shader->addShaderFromSourceCode(QOpenGLShader::Fragment, shader->getFragmentSrc());
    shader->link();
    shader->bind();

    vao->create();
    vao->bind();

    buffer->add("aPos", new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer));
    buffer->buildVertexBuffer<QVector3D>("aPos", vertices, 3, 0, shader);

    vao->release();
    buffer->releaseAll();
    shader->release();

    //------------------------------------------------------- //

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

QDataStream& operator<<(QDataStream& out, const Game& game)
{
    out << *game.getIETime() << *game.getIEInput() << *game.getIEScene();

    return out;
}

QDataStream& operator>>(QDataStream& in, Game& game)
{
    game.shutdown();

    IETime* time = new IETime(0, 0, &game);
    IEInput* input = new IEInput(&game, &game);
    IEScene* scene = new IEScene(&game);

    in >> *time >> *input >> *scene;

    game.setIETime(time);
    game.setIEInput(input);
    game.setIEScene(scene);

    game.startup();

    return in;
}

