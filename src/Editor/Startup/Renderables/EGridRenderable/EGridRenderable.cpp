#include "EGridRenderable.h"
#include "EGridMesh.h"
#include "EGridShader.h"
#include "IEVertexBuffer.h"
#include "IECamera.h"
#include <QVector3D>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLExtraFunctions>

EGridRenderable::EGridRenderable() :
    gridMesh(new EGridMesh),
    gridShader(new EGridShader),
    vao(new QOpenGLVertexArrayObject),
    posBuffer(new IEVertexBuffer<QVector3D>(gridMesh->getPosVertices(), 12, 3, 0, 0, 0))
{
    setup();
}

EGridRenderable::~EGridRenderable()
{
    vao->destroy();

    delete gridMesh;
    delete gridShader;
    delete vao;
    delete posBuffer;
}

void EGridRenderable::setup()
{
    gridShader->build();
    vao->create();

    gridShader->bind();
    vao->bind();
    posBuffer->build(gridShader->attributeLocation("aPos"));

    gridShader->release();
    vao->release();
    posBuffer->release();
}

void EGridRenderable::draw(QOpenGLExtraFunctions* glFunc, IECamera* camera)
{
    gridShader->bind();
    vao->bind();

    gridShader->setUniformValue("uViewProjection", camera->getViewProjection());

    glFunc->glDrawArrays(GL_TRIANGLES, 0, 6);

    gridShader->release();
    vao->release();
}
