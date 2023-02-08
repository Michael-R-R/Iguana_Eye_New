#include "IEShader.h"
#include "IEFile.h"

IEShader::IEShader() :
    QOpenGLShaderProgram(), IEResource(0),
    vertexSource(), fragmentSource()
{

}

IEShader::IEShader(unsigned long long id) :
    QOpenGLShaderProgram(), IEResource(id),
    vertexSource(), fragmentSource()
{

}

IEShader::IEShader(unsigned long long id, QString vSrc, QString fSrc) :
    QOpenGLShaderProgram(), IEResource(id),
    vertexSource(vSrc), fragmentSource(fSrc)
{

}

IEShader::IEShader(unsigned long long id, QString filePath) :
    QOpenGLShaderProgram(), IEResource(id),
    vertexSource(), fragmentSource()
{
    parseFile(filePath);
}

IEShader::IEShader(const IEShader& other) :
    QOpenGLShaderProgram(), IEResource(0),
    vertexSource(other.vertexSource), fragmentSource(other.fragmentSource)
{

}

IEShader::~IEShader()
{

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

void IEShader::parseFile(QString filePath)
{
    QString content = "";
    if(!IEFile::read(filePath, &content))
        return;

    if(content.isEmpty())
        return;

    QString vDelimiter = "[VERTEX]";
    QString fDelimiter = "[FRAGMENT]";

    int vIndex = content.indexOf(vDelimiter);
    int fIndex = content.indexOf(fDelimiter);
    if(vIndex < 0 || fIndex < 0)
        return;

    int vStart = vIndex + vDelimiter.length() + 1;
    int vEnd = fIndex - vStart;
    vertexSource = content.mid(vStart, vEnd);

    int fStart = fIndex + fDelimiter.length() + 1;
    fragmentSource = content.mid(fStart);
}

QDataStream& operator<<(QDataStream& out, const IEShader& shader)
{
    out << shader.getId() << shader.getVertexSrc() << shader.getFragmentSrc();

    return out;
}

QDataStream& operator>>(QDataStream& in, IEShader& shader)
{
    unsigned long long id = 0;
    QString vSrc;
    QString fSrc;

    in >> id >> vSrc >> fSrc;

    shader.setId(id);
    shader.setVertexSrc(vSrc);
    shader.setFragmentSrc(fSrc);

    return in;
}
