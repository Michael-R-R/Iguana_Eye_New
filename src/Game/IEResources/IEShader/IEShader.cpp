#include "IEShader.h"
#include "IEFile.h"

IEShader::IEShader() :
    QOpenGLShaderProgram(), IEResource(0),
    vertexSource(), fragmentSource()
{

}

IEShader::IEShader(unsigned long long id) :
    QOpenGLShaderProgram(), IEResource(id),
    vertexSource("#version 430 core\n\nvoid main()\n{\n\t\n}\n"),
    fragmentSource("#version 430 core\n\nvoid main()\n{\n\t\n}\n")
{

}

IEShader::IEShader(unsigned long long id, const QString& vSrc, const QString& fSrc) :
    QOpenGLShaderProgram(), IEResource(id),
    vertexSource(vSrc), fragmentSource(fSrc)
{

}

IEShader::IEShader(const IEShader& other) :
    QOpenGLShaderProgram(), IEResource(0),
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
