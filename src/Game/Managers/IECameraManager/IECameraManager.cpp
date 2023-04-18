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

    for(auto* i : manager.resources)
    {
        out << i->getFilePath();

        IESerialize::write<IECamera>(i->getFilePath(), static_cast<IECamera*>(i));
    }

    return out;
}

QDataStream& IECameraManager::deserialize(QDataStream& in, Serializable& obj)
{
    auto& manager = static_cast<IECameraManager&>(obj);
    manager.clear();

    int size = 0;
    in >> size;

    QString path = "";
    for(int i = 0; i < size; i++)
    {
        in >> path;

        auto camera = new IECamera(path, &manager);
        if(!IESerialize::read<IECamera>(path, camera))
        {
            delete camera;
            continue;
        }

        if(!manager.add(camera->getId(), camera))
            delete camera;
    }

    return in;
}
