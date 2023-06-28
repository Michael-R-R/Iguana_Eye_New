#include "IESceneResource.h"
#include "IEHash.h"

IESceneResource::IESceneResource(QObject* parent) :
    IEResource(parent)
{

}

IESceneResource::IESceneResource(const QString& path, QObject* parent) :
    IEResource(parent)
{
    name = path;
    id = IEHash::Compute(name);
}

IESceneResource::~IESceneResource()
{

}

uint64_t IESceneResource::updateId(const QString& path)
{
    name = path;
    id = IEHash::Compute(name);

    emit nameUpdated(id, name);

    return id;
}

QDataStream& IESceneResource::serialize(QDataStream& out, const Serializable& obj) const
{
    return IEResource::serialize(out, obj);
}

QDataStream& IESceneResource::deserialize(QDataStream& in, Serializable& obj)
{
    return IEResource::deserialize(in, obj);
}
