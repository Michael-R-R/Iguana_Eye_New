#include "IEShader.h"
#include "IEFile.h"

IEShader::IEShader(QObject* parent) :
    QOpenGLShaderProgram(),
    IEResource(parent),
    vertexSource(), fragmentSource()
{

}

IEShader::IEShader(const QString& path, QObject* parent) :
    QOpenGLShaderProgram(),
    IEResource(path, parent),
    vertexSource(),
    fragmentSource()
{

}

IEShader::~IEShader()
{
    this->removeAllShaders();
}

void IEShader::build()
{
    if(this->shaders().size() > 0)
        this->removeAllShaders();

    this->create();
    this->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexSource);
    this->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentSource);
    this->link();
}

QDataStream& IEShader::serialize(QDataStream& out, const Serializable& obj) const
{
    return IEResource::serialize(out, obj);
}

QDataStream& IEShader::deserialize(QDataStream& in, Serializable& obj)
{
    return IEResource::deserialize(in, obj);
}
