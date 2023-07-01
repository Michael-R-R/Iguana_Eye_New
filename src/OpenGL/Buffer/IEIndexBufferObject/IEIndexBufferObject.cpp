#include "IEIndexBufferObject.h"

IEIndexBufferObject::IEIndexBufferObject(QObject* parent) :
    IEBufferObject(QOpenGLBuffer::IndexBuffer, parent)
{

}

IEIndexBufferObject::~IEIndexBufferObject()
{

}

int IEIndexBufferObject::appendValue(const unsigned val)
{
    const int index = values.size();
    values.append(val);
    return index;
}

bool IEIndexBufferObject::removeValue(const int index)
{
    if(index < 0 || index >= values.size())
        return false;

    const int lastIndex = values.size() - 1;
    values[index] = values[lastIndex];
    values.removeLast();

    return true;
}

unsigned IEIndexBufferObject::getValue(const int index)
{
    if(index < 0 || index >= values.size())
        return 0;

    return values[index];
}

void IEIndexBufferObject::setValue(const int index, const unsigned val)
{
    if(index < 0 || index >= values.size())
        return;

    values[index] = val;
}

void IEIndexBufferObject::handleAllocate(const bool doRelease)
{
    this->bind();

    this->allocate(values.constData(), (int)(values.size() * sizeof(unsigned)));

    if(doRelease)
        this->release();
}

void IEIndexBufferObject::handleSuballocate(const int index)
{
    if(index < 0 || index > values.size() - 1)
        return;

    if(!isCreated())
        return;

    int typeSize = sizeof(unsigned);

    this->bind();
    this->write((index * typeSize), &values[index], typeSize);
    this->release();
}

void IEIndexBufferObject::build(const int)
{
    if(this->isCreated())
        this->destroy();

    this->create();
    this->handleAllocate();
}

int IEIndexBufferObject::size() const
{
    return values.size();
}

QDataStream& IEIndexBufferObject::serialize(QDataStream& out, const Serializable& obj) const
{
    IEBufferObject::serialize(out, obj);

    const auto& buffer = static_cast<const IEIndexBufferObject&>(obj);

    out << buffer.values;

    return out;
}

QDataStream& IEIndexBufferObject::deserialize(QDataStream& in, Serializable& obj)
{
    IEBufferObject::deserialize(in, obj);

    auto& buffer = static_cast<IEIndexBufferObject&>(obj);

    in >> buffer.values;

    return in;
}
