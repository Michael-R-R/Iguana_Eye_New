#include "EGridRenderable.h"
#include "EGridMesh.h"
#include "EGridShader.h"
#include "IECamera.h"
#include "IEBufferObject.h"
#include "IEBufferObjectFactory.h"
#include <QOpenGLContext>
#include <QOpenGLFunctions>

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
    IEMeshNode* meshNode = gridMesh->getNode(0);
    posBuffer->setValues(meshNode->positions);

    gridShader->build();
    vao->create();

    gridShader->bind();
    vao->bind();
    posBuffer->build(gridShader->attributeLocation("aPos"));

    gridShader->release();
    vao->release();
    posBuffer->release();
}

void EGridRenderable::draw(IECamera* camera)
{
    gridShader->bind();
    vao->bind();

    gridShader->setMat4("uViewProjection", camera->getViewProjection());

    auto* gl = QOpenGLContext::currentContext()->functions();
    gl->glDrawArrays(GL_TRIANGLES, 0, 6);

    gridShader->release();
    vao->release();
}
