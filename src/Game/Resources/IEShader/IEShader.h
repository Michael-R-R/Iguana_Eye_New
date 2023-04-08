#pragma once

#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QString>

#include "IEResource.h"

class IEShader : public QOpenGLShaderProgram, public IEResource
{
protected:
    QString vertexSource;
    QString fragmentSource;

public:
    IEShader();
    IEShader(const QString& path);
    IEShader(const IEShader&) = delete;
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

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};
