#include "IEResource.h"
#include "IEHash.h"

IEResource::IEResource() :
    filePath(""), id(0)
{

}

IEResource::IEResource(const QString& path) :
    filePath(path), id(IEHash::Compute(path))
{

}

IEResource::~IEResource()
{

}

unsigned long long IEResource::updatePath(const QString& path)
{
    if(path.isEmpty())
        return 0;

    filePath = path;
    id = IEHash::Compute(path);

    return id;
}


QDataStream& IEResource::serialize(QDataStream& out, const Serializable& obj) const
{
    const IEResource& resource = static_cast<const IEResource&>(obj);

    out << resource.filePath << resource.id;

    return out;
}

QDataStream& IEResource::deserialize(QDataStream& in, Serializable& obj)
{
    IEResource& resource = static_cast<IEResource&>(obj);

    in >> resource.filePath >> resource.id;

    return in;
}
