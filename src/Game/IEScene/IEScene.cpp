#include "IEScene.h"

IEScene::IEScene(QObject* parent) :
    IEObject(parent),
    nameManager(new IENameManager(this))
{

}

IEScene::~IEScene()
{

}
