#pragma once

#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QString>

#include "IEFileResource.h"

class IEShader : public QOpenGLShaderProgram, public IEFileResource
{
protected:
    QString vertexSource;
    QString fragmentSource;

public:
    IEShader(QObject* parent = nullptr);
    IEShader(const QString& path, QObject* parent = nullptr);
    IEShader(const IEShader&) = delete;
    virtual ~IEShader();

    bool operator==(const IEShader& other) { return IEResource::operator==(other); }
    bool operator!=(const IEShader& other) { return IEResource::operator!=(other); }
    bool operator<(const IEShader& other) { return IEResource::operator<(other); }
    bool operator>(const IEShader& other) { return IEResource::operator>(other); }

    bool build();

    QString getVertexSrc() const { return vertexSource; }
    QString getFragmentSrc() const { return fragmentSource; }

    void setVertexSrc(const QString& val) { vertexSource = val; }
    void setFragmentSrc(const QString& val) { fragmentSource = val; }

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};
