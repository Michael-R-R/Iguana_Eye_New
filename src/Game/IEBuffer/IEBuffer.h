#pragma once

#include <QMap>
#include <QString>
#include <QVector>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>

#include "IEShader.h"

class IEBuffer
{
    QMap<QString, QOpenGLBuffer*> buffers;

public:
    IEBuffer();
    ~IEBuffer();

    void clear();
    bool add(const QString key, QOpenGLBuffer* value);
    bool remove(const QString& key);
    bool doesExist(const QString& key) const;
    bool bind(const QString& key);
    bool release(const QString& key);
    void releaseAll();

    void buildIndexBuffer(const QString& key, QVector<unsigned>& data)
    {
        QOpenGLBuffer* buffer = buffers[key];
        if(!buffer || buffer->type() != QOpenGLBuffer::IndexBuffer)
            return;

        buffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
        buffer->create();
        buffer->bind();
        buffer->allocate(data.data(), (int)(data.size() * sizeof(unsigned)));
    }

    template<class T>
    void buildVertexBuffer(const QString& key, QVector<T>& data,
                           int tupleSize, int divisorSize, IEShader* shader)
    {
        QOpenGLBuffer* buffer = buffers[key];
        if(!buffer || buffer->type() != QOpenGLBuffer::VertexBuffer)
            return;

        buffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
        buffer->create();
        buffer->bind();
        buffer->allocate(data.data(), (int)(data.size() * sizeof(T)));

        int attribLoc = shader->attributeLocation(key);

        QOpenGLFunctions* func = QOpenGLContext::currentContext()->functions();
        if(divisorSize < 1)
        {
            func->glVertexAttribPointer(attribLoc, tupleSize, GL_FLOAT, false, 0, 0);
            func->glEnableVertexAttribArray(attribLoc);
        }
        else
        {
            QOpenGLExtraFunctions* extraFunc = QOpenGLContext::currentContext()->extraFunctions();
            for(int i = 0; i < divisorSize; i++)
            {
                func->glVertexAttribPointer(attribLoc + i, tupleSize, GL_FLOAT, false, 0, (void*)(i * sizeof(T)));
                func->glEnableVertexAttribArray(attribLoc + i);
                extraFunc->glVertexBindingDivisor(attribLoc + i, 1);
            }
        }
    }
};

