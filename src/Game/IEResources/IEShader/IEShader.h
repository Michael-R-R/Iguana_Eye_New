#pragma once

#include <QDataStream>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QString>

#include "IEResource.h"

class IEShader : public QOpenGLShaderProgram, public IEResource
{
    QString vertexSource;
    QString fragmentSource;

public:
    IEShader();
    IEShader(const QString& path, unsigned long long id);
    IEShader(const IEShader& other);
    ~IEShader();

    bool operator==(const IEShader& other) { return IEResource::operator==(other); }
    bool operator!=(const IEShader& other) { return IEResource::operator!=(other); }
    bool operator<(const IEShader& other) { return IEResource::operator<(other); }
    bool operator>(const IEShader& other) { return IEResource::operator>(other); }

    void build();

    QString getVertexSrc() const { return vertexSource; }
    QString getFragmentSrc() const { return fragmentSource; }

    void setVertexSrc(const QString& val) { vertexSource = val; }
    void setFragmentSrc(const QString& val) { fragmentSource = val; }

public:
    friend QDataStream& operator<<(QDataStream& out, const IEShader& shader)
    {
        out << shader.filePath
            << shader.id
            << shader.vertexSource
            << shader.fragmentSource;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEShader& shader)
    {
        in >> shader.filePath
           >> shader.id
           >> shader.vertexSource
           >> shader.fragmentSource;

        return in;
    }
};
