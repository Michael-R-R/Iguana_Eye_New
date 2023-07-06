#include "IEObject.h"

IEObject::IEObject(QObject* parent) :
    QObject(parent)
{

}

IEObject::~IEObject()
{

}


QDataStream& IEObject::serialize(QDataStream& out, const IESerializable&) const
{
    return out;
}

QDataStream& IEObject::deserialize(QDataStream& in, IESerializable&)
{
    return in;
}
