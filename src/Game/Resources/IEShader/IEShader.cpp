#include "IEShader.h"
#include "IEFile.h"

IEShader::IEShader() :
    QOpenGLShaderProgram(),
    IEResource(),
    vertexSource(), fragmentSource()
{

}

IEShader::IEShader(const QString& path) :
    QOpenGLShaderProgram(),
    IEResource(path),
    vertexSource("#version 430 core\n\nvoid main()\n{\n\t\n}\n\n"),
    fragmentSource("#version 430 core\n\nvoid main()\n{\n\t\n}\n\n")
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
    IEResource::serialize(out, obj);

    const IEShader& shader = static_cast<const IEShader&>(obj);

    out << shader.vertexSource << shader.fragmentSource;

    return out;
}

QDataStream& IEShader::deserialize(QDataStream& in, Serializable& obj)
{
    IEResource::deserialize(in, obj);

    IEShader& shader = static_cast<IEShader&>(obj);

    in >> shader.vertexSource >> shader.fragmentSource;

    return in;
}
