#include "IEBuffer.h"

IEBuffer::IEBuffer() :
    buffers()
{

}

IEBuffer::~IEBuffer()
{
    clear();
}

void IEBuffer::clear()
{
    QMapIterator<QString, QOpenGLBuffer*> it(buffers);
    while(it.hasNext())
    {
        it.next();

        auto temp = it.value();
        buffers[it.key()] = nullptr;
        delete temp;
    }

    buffers.clear();
}

bool IEBuffer::add(const QString key, QOpenGLBuffer* value)
{
    if(doesExist(key))
        return false;

    buffers[key] = value;

    return true;
}

bool IEBuffer::remove(const QString& key)
{
    if(!doesExist(key))
        return false;

    auto temp = buffers[key];
    buffers.remove(key);
    delete temp;

    return true;
}

bool IEBuffer::bind(const QString& key)
{
    if(!doesExist(key))
        return false;

    QOpenGLBuffer* buffer = buffers[key];
    if(!buffer)
        return false;

    buffer->bind();

    return true;
}

bool IEBuffer::release(const QString& key)
{
    if(!doesExist(key))
        return false;

    QOpenGLBuffer* buffer = buffers[key];
    if(!buffer)
        return false;

    buffer->release();

    return true;
}

void IEBuffer::releaseAll()
{
    for(auto& buffer : buffers)
    {
        buffer->release();
    }
}

bool IEBuffer::doesExist(const QString& key) const
{
    return buffers.contains(key);
}

QDataStream& operator<<(QDataStream& out, const IEBuffer& buffer)
{
    int size = buffer.getBuffers().size();
    out << size;

    QMapIterator<QString, QOpenGLBuffer*> it(buffer.getBuffers());
    while(it.hasNext())
    {
        it.next();

        out << it.key() << it.value()->type();
    }

    return out;
}

QDataStream& operator>>(QDataStream& in, IEBuffer& buffer)
{
    QMap<QString, QOpenGLBuffer*> buffers;
    int size = 0;

    in >> size;

    for(int i = 0; i < size; i++)
    {
        QString key;
        QOpenGLBuffer::Type type;

        in >> key >> type;

        auto tempBuffer = new QOpenGLBuffer(type);

        buffers[key] = tempBuffer;
    }

    buffer.setBuffers(buffers);

    return in;
}
