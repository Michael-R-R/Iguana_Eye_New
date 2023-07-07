#include "EGridRenderable.h"
#include "EGridMesh.h"
#include "EGridShader.h"
#include "IECamera.h"
#include "IEBufferObject.h"
#include "IEBufferObjectFactory.h"

EGridRenderable::EGridRenderable(QObject* parent) :
    IEObject(parent),
    gridMesh(new EGridMesh(this)),
    gridShader(new EGridShader(this)),
    vao(new QOpenGLVertexArrayObject(this)),
    posBuffer(IEBufferObjectFactory::make(IEBufferType::Vec3, 0, 0, 0, this))
{
    setup();
}

EGridRenderable::~EGridRenderable()
{
    vao->destroy();
}

void EGridRenderable::setup()
{
    posBuffer->setValues(gridMesh->getPosVertices());

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
