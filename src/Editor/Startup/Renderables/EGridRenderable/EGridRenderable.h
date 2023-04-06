#pragma once

class EGridMesh;
class EGridShader;
class QVector3D;
class QOpenGLVertexArrayObject;
class QOpenGLExtraFunctions;
class IECamera;

template<class T>
class IEVertexBuffer;

class EGridRenderable
{
    EGridMesh* gridMesh;
    EGridShader* gridShader;
    QOpenGLVertexArrayObject* vao;
    IEVertexBuffer<QVector3D>* posBuffer;

public:
    EGridRenderable();
    ~EGridRenderable();

    void setup();
    void draw(QOpenGLExtraFunctions* glFunc, IECamera* camera);
};

