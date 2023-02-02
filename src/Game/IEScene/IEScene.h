#pragma once

#include "IEObject.h"
#include "IENameManager.h"

class IEScene : public IEObject
{
    Q_OBJECT

    IENameManager* nameManager;

public:
    IEScene(QObject* parent = nullptr);
    ~IEScene();


    IENameManager* getNameManager() const { return nameManager; }
};
