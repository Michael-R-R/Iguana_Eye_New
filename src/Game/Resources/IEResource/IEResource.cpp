#include "IEResource.h"
#include "IEHash.h"

IEResource::IEResource(QObject* parent) :
    IEObject(parent),
    name(""), id(0)
{

}

IEResource::~IEResource()
{

}

QDataStream& IEResource::serialize(QDataStream& out, const IESerializable& obj) const
{
    const IEResource& resource = static_cast<const IEResource&>(obj);

    out << resource.name << resource.id;

    return out;
}

QDataStream& IEResource::deserialize(QDataStream& in, IESerializable& obj)
{
    IEResource& resource = static_cast<IEResource&>(obj);

    in >> resource.name >> resource.id;

    return in;
}
