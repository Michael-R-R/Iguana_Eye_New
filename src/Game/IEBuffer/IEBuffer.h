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

    template<class T>
    void buildIndexBuffer(const QString& name, QVector<T>& data, int typeSize)
    {
        QOpenGLBuffer* buffer = buffers[name];
        if(!buffer || buffer->type() != QOpenGLBuffer::IndexBuffer)
            return;

        buffer->create();
        buffer->bind();
        buffer->allocate(data.data(), data.size() * typeSize);
        buffer->release();
    }

    template<class T>
    void buildVertexBuffer(const QString& name, QVector<T>& data, int typeSize,
                           int tupleSize, int stride, int divisorSize, IEShader* shader)
    {
        QOpenGLBuffer* buffer = buffers[name];
        if(!buffer || buffer->type() != QOpenGLBuffer::VertexBuffer)
            return;

        buffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
        buffer->create();
        buffer->bind();
        buffer->allocate(data.data(), data.size() * typeSize);

        int attribLoc = shader->attributeLocation(name);

        QOpenGLFunctions* func = QOpenGLContext::currentContext()->functions();
        if(divisorSize < 1)
        {
            func->glVertexAttribPointer(attribLoc, tupleSize, GL_FLOAT, false, stride, 0);
            func->glEnableVertexAttribArray(attribLoc);
        }
        else
        {
            QOpenGLExtraFunctions* extraFunc = QOpenGLContext::currentContext()->extraFunctions();

            for(int i = 0; i < divisorSize; i++)
            {
                func->glVertexAttribPointer(attribLoc + i, tupleSize, GL_FLOAT, false, stride, i * typeSize);
                func->glEnableVertexAttribArray(attribLoc + i);
                extraFunc->glVertexBindingDivisor(attribLoc + i, 1);
            }
        }

        buffer->release();
    }
};

