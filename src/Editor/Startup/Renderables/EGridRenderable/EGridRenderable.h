#pragma once

#include "IEObject.h"

class EGridMesh;
class EGridShader;
class QVector3D;
class QOpenGLVertexArrayObject;
class QOpenGLExtraFunctions;
class IECamera;

template<class T>
class IEVertexBuffer;

class EGridRenderable : public IEObject
{
    EGridMesh* gridMesh;
    EGridShader* gridShader;
    QOpenGLVertexArrayObject* vao;
    IEVertexBuffer<QVector3D>* posBuffer;

public:
    EGridRenderable(QObject* parent = nullptr);
    ~EGridRenderable();

    void setup();
    void draw(QOpenGLExtraFunctions* glFunc, IECamera* camera);
};

