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

QDataStream& IECameraManager::serialize(QDataStream& out, const IESerializable& obj) const
{
    IEResourceManager::serialize(out, obj);

    const auto& manager = static_cast<const IECameraManager&>(obj);

    out << (int)manager.resources.size();

    foreach (auto* i, manager.resources)
    {
        out << *i;
    }

    return out;
}

QDataStream& IECameraManager::deserialize(QDataStream& in, IESerializable& obj)
{
    IEResourceManager::deserialize(in, obj);

    auto& manager = static_cast<IECameraManager&>(obj);

    int count = 0;
    in >> count;

    for(int i = 0; i < count; i++)
    {
        auto* camera = new IECamera(&manager);

        in >> *camera;

        if(!manager.add(camera->getId(), camera))
            delete camera;
    }

    return in;
}
