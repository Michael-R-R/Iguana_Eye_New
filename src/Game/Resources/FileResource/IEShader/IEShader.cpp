#include "IEShader.h"
#include "IEFile.h"
#include <QOpenGLContext>
#include <QOpenGLFunctions>

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

void IEShader::setBool(const char* name, const bool val)
{
    auto* gl = QOpenGLContext::currentContext()->functions();
    const int loc = gl->glGetUniformLocation(this->programId(), name);
    gl->glUniform1i(loc, val);
}

void IEShader::setInt(const char* name, const int val)
{
    auto* gl = QOpenGLContext::currentContext()->functions();
    const int loc = gl->glGetUniformLocation(this->programId(), name);
    gl->glUniform1i(loc, val);
}

void IEShader::setFloat(const char* name, const float val)
{
    auto* gl = QOpenGLContext::currentContext()->functions();
    const int loc = gl->glGetUniformLocation(this->programId(), name);
    gl->glUniform1f(loc, val);
}

void IEShader::setVec2(const char* name, const glm::vec2& val)
{
    auto* gl = QOpenGLContext::currentContext()->functions();
    const int loc = gl->glGetUniformLocation(this->programId(), name);
    gl->glUniform2fv(loc, 1, &val[0]);
}

void IEShader::setVec3(const char* name, const glm::vec3& val)
{
    auto* gl = QOpenGLContext::currentContext()->functions();
    const int loc = gl->glGetUniformLocation(this->programId(), name);
    gl->glUniform3fv(loc, 1, &val[0]);
}

void IEShader::setVec4(const char* name, const glm::vec4& val)
{
    auto* gl = QOpenGLContext::currentContext()->functions();
    const int loc = gl->glGetUniformLocation(this->programId(), name);
    gl->glUniform4fv(loc, 1, &val[0]);
}

void IEShader::setMat2(const char* name, const glm::mat3& val)
{
    auto* gl = QOpenGLContext::currentContext()->functions();
    const int loc = gl->glGetUniformLocation(this->programId(), name);
    gl->glUniformMatrix2fv(loc, 1, GL_FALSE, &val[0][0]);
}

void IEShader::setMat3(const char* name, const glm::mat3& val)
{
    auto* gl = QOpenGLContext::currentContext()->functions();
    const int loc = gl->glGetUniformLocation(this->programId(), name);
    gl->glUniformMatrix3fv(loc, 1, GL_FALSE, &val[0][0]);
}

void IEShader::setMat4(const char* name, const glm::mat4& val)
{
    auto* gl = QOpenGLContext::currentContext()->functions();
    const int loc = gl->glGetUniformLocation(this->programId(), name);
    gl->glUniformMatrix4fv(loc, 1, GL_FALSE, &val[0][0]);
}

QDataStream& IEShader::serialize(QDataStream& out, const IESerializable& obj) const
{
    return IEFileResource::serialize(out, obj);
}

QDataStream& IEShader::deserialize(QDataStream& in, IESerializable& obj)
{
    return IEFileResource::deserialize(in, obj);
}
