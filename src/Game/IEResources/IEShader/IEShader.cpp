#include "IEShader.h"
#include "IEFile.h"

IEShader::IEShader() :
    QOpenGLShaderProgram(),
    IEResource("", 0),
    vertexSource(), fragmentSource()
{

}

IEShader::IEShader(const QString& path, unsigned long long id) :
    QOpenGLShaderProgram(),
    IEResource(path, id),
    vertexSource("#version 430 core\n\nvoid main()\n{\n\t\n}\n"),
    fragmentSource("#version 430 core\n\nvoid main()\n{\n\t\n}\n")
{

}

IEShader::IEShader(const IEShader& other) :
    QOpenGLShaderProgram(),
    IEResource(other.filePath, other.id),
    vertexSource(other.vertexSource), fragmentSource(other.fragmentSource)
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

    if(this->programId() < 1)
        this->create();

    this->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexSource);
    this->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentSource);
    this->link();
}
