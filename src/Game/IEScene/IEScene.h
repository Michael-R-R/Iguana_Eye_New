#pragma once

#include <QDataStream>

#include "IEObject.h"
#include "IENameManager.h"
#include "IEShaderManager.h"

class IEScene : public IEObject
{
    Q_OBJECT

    IENameManager* nameManager;
    IEShaderManager* shaderManager;

public:
    IEScene(QObject* parent = nullptr);
    ~IEScene();

    IENameManager* getNameManager() const { return nameManager; }
    IEShaderManager* getShaderManager() const { return shaderManager; }

    void setNameManager(IENameManager* val) { nameManager = val; }
    void setShaderManager(IEShaderManager* val) { shaderManager = val; }
};

QDataStream& operator<<(QDataStream& out, const IEScene& scene);
QDataStream& operator>>(QDataStream& in, IEScene& scene);
