#pragma once

#include <QSharedPointer>

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
    QSharedPointer<EGridMesh> gridMesh;
    QSharedPointer<EGridShader> gridShader;
    QSharedPointer<QOpenGLVertexArrayObject> vao;
    QSharedPointer<IEVertexBuffer<QVector3D>> posBuffer;

public:
    EGridRenderable();
    ~EGridRenderable();

    void setup();
    void draw(QOpenGLExtraFunctions* glFunc, QSharedPointer<IECamera> camera);
};

