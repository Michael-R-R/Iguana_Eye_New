#pragma once

#include <QDataStream>

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

    void setNameManager(IENameManager* val) { nameManager = val; }
};

QDataStream& operator<<(QDataStream& out, const IEScene& scene);
QDataStream& operator>>(QDataStream& in, IEScene& scene);
