#pragma once

#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QString>
#include <QDataStream>

#include "IEResource.h"

class IEShader : public QOpenGLShaderProgram, public IEResource
{
    QString vertexSource;
    QString fragmentSource;

public:
    IEShader();
    IEShader(unsigned long long id);
    IEShader(unsigned long long id, QString vSrc, QString fSrc);
    IEShader(unsigned long long id, QString filePath);
    ~IEShader();

    bool operator==(const IEShader& other) { return IEResource::operator==(other); }
    bool operator!=(const IEShader& other) { return IEResource::operator!=(other); }
    bool operator<(const IEShader& other) { return IEResource::operator<(other); }
    bool operator>(const IEShader& other) { return IEResource::operator>(other); }

    const QString& getVertexSrc() const { return vertexSource; }
    const QString& getFragmentSrc() const { return fragmentSource; }

    void setVertexSrc(const QString val) { vertexSource = val; }
    void setFragmentSrc(const QString val) { fragmentSource = val; }

private:
    void parseFile(QString filePath);
};

QDataStream& operator<<(QDataStream& out, const IEShader& shader);
QDataStream& operator>>(QDataStream& in, IEShader& shader);
