#pragma once

#include <QOpenGLVertexArrayObject>
#include <QOpenGLExtraFunctions>
#include <QVector3D>

#include "IEObject.h"

class EGridMesh;
class EGridShader;
class IEBufferObject;
class IECamera;

class EGridRenderable : public IEObject
{
    EGridMesh* gridMesh;
    EGridShader* gridShader;
    QOpenGLVertexArrayObject* vao;
    IEBufferObject* posBuffer;

public:
    EGridRenderable(QObject* parent = nullptr);
    ~EGridRenderable();

    void setup();
    void draw(QOpenGLExtraFunctions* glFunc, IECamera* camera);
};

