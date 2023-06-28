#include "IECameraManager.h"
#include "IECamera.h"
#include "IESerialize.h"

IECameraManager::IECameraManager(QObject* parent) :
    IEResourceManager(parent)
{

}

IECameraManager::~IECameraManager()
{

}

QDataStream& IECameraManager::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& manager = static_cast<const IECameraManager&>(obj);

    out << (int)manager.resources.size();

    for(auto* i : qAsConst(manager.resources))
    {
        auto* camera = static_cast<IECamera*>(i);

        out << *camera;
    }

    return out;
}

QDataStream& IECameraManager::deserialize(QDataStream& in, Serializable& obj)
{
    auto& manager = static_cast<IECameraManager&>(obj);

    int size = 0;
    in >> size;

    for(int i = 0; i < size; i++)
    {
        auto* camera = new IECamera(&manager);

        in >> *camera;

        if(!manager.add(camera->getId(), camera))
            delete camera;
    }

    return in;
}
