#include "IEIndexBufferObject.h"

IEIndexBufferObject::IEIndexBufferObject(QObject* parent) :
    IEBufferObject(QOpenGLBuffer::IndexBuffer, IEBufferType::Index, false, parent),
    values()
{

}

IEIndexBufferObject::IEIndexBufferObject(const QVector<unsigned int>& vals, QObject* parent) :
    IEBufferObject(QOpenGLBuffer::IndexBuffer, IEBufferType::Index, false, parent),
    values(vals)
{

}

IEIndexBufferObject::~IEIndexBufferObject()
{

}

int IEIndexBufferObject::appendValue(const std::any& val)
{
    const int index = values.size();

    if(val.has_value())
        values.append(std::any_cast<unsigned>(val));
    else
        values.append(0);

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

std::any IEIndexBufferObject::getValue(const int index)
{
    if(index < 0 || index >= values.size())
        return std::any();

    return values[index];
}

std::any IEIndexBufferObject::getValues() const
{
    return values;
}

void IEIndexBufferObject::setValue(const int index, const std::any& val)
{
    if(index < 0 || index >= values.size())
        return;

    values[index] = (val.has_value()) ? std::any_cast<unsigned>(val) : 0;
}

void IEIndexBufferObject::setValues(const std::any& val)
{
    values = (val.has_value()) ? std::any_cast<QVector<unsigned>>(val) : QVector<unsigned>{};
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
