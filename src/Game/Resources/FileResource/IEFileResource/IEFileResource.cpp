#include "IEFileResource.h"
#include "IEHash.h"
#include "IEFile.h"

IEFileResource::IEFileResource(QObject* parent) :
    IEResource(parent)
{

}

IEFileResource::IEFileResource(const QString& path, QObject* parent) :
    IEResource(parent)
{
    name = IEFile::absolutePath(path);
    id = IEHash::Compute(name);
}

IEFileResource::~IEFileResource()
{

}

uint64_t IEFileResource::updateId(const QString& path)
{
    name = IEFile::absolutePath(path);
    id = IEHash::Compute(name);

    emit nameUpdated(id, name);

    return id;
}

QDataStream& IEFileResource::serialize(QDataStream& out, const Serializable& obj) const
{
    return IEResource::serialize(out, obj);
}

QDataStream& IEFileResource::deserialize(QDataStream& in, Serializable& obj)
{
    return IEResource::deserialize(in, obj);
}

