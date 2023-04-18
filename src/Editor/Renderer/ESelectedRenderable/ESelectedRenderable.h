#pragma once

#include <QMap>

#include "IEObject.h"

class EPhysicsEngine;
class QOpenGLExtraFunctions;
class IEShader;
class IEEntity;
class IECamera;

class ESelectedRenderable : public IEObject
{
    Q_OBJECT

    IEShader* shader;
    QMap<int, IEEntity> entities;

public:
    ESelectedRenderable(EPhysicsEngine* physicsEngine, QObject* parent = nullptr);
    ~ESelectedRenderable();

    void predraw(QOpenGLExtraFunctions* glFunc);
    void draw(QOpenGLExtraFunctions* glFunc, IECamera* camera);

public slots:
    void addEntity(const IEEntity& entity);
    void clearSelection();
};

