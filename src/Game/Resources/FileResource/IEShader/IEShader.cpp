#include "IEShader.h"
#include "IEFile.h"

IEShader::IEShader(QObject* parent) :
    QOpenGLShaderProgram(),
    IEFileResource(parent),
    vertexSource(),
    fragmentSource()
{

}

IEShader::IEShader(const QString& path, QObject* parent) :
    QOpenGLShaderProgram(),
    IEFileResource(path, parent),
    vertexSource(),
    fragmentSource()
{

}

IEShader::~IEShader()
{
    this->removeAllShaders();
}

bool IEShader::build()
{
    if(this->shaders().size() > 0)
        this->removeAllShaders();

    if(!this->create())
        return false;

    if(!this->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexSource))
    {
        this->removeAllShaders();
        return false;
    }

    if(!this->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentSource))
    {
        this->removeAllShaders();
        return false;
    }

    if(!this->link())
    {
        this->removeAllShaders();
        return false;
    }

    return true;
}

QDataStream& IEShader::serialize(QDataStream& out, const IESerializable& obj) const
{
    return IEFileResource::serialize(out, obj);
}

QDataStream& IEShader::deserialize(QDataStream& in, IESerializable& obj)
{
    return IEFileResource::deserialize(in, obj);
}
