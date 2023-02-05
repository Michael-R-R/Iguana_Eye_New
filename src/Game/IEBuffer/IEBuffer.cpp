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

bool IEBuffer::doesExist(const QString& key) const
{
    return buffers.contains(key);
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
    QMapIterator<QString, QOpenGLBuffer*> it(buffers);
    while(it.hasNext())
    {
        it.next();

        it.value()->release();
    }
}
