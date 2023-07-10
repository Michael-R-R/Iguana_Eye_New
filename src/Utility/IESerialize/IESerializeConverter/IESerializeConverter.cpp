#include "IESerializeConverter.h"
#include "GLSViewProjection.h"
#include "GLSCamera.h"

void IESerializeConverter::write(QDataStream& out, const std::any& val)
{
    size_t hashcode = val.type().hash_code();

    if(hashcode == hashcodes[0]) { out << hashcode; write(out, std::any_cast<glm::vec2>(val)); }
    else if(hashcode == hashcodes[1]) { out << hashcode; write(out, std::any_cast<glm::vec3>(val)); }
    else if(hashcode == hashcodes[2]) { out << hashcode; write(out, std::any_cast<glm::vec4>(val)); }
    else if(hashcode == hashcodes[3]) { out << hashcode; write(out, std::any_cast<glm::mat4>(val)); }
    else { out << typeid(char).hash_code() << (char)'~'; }
}

void IESerializeConverter::write(QDataStream& out, const glm::vec2& val)
{
    for(int i = 0; i < 2; i++)
    {
        out << val[i];
    }
}

void IESerializeConverter::write(QDataStream& out, const glm::vec3& val)
{
    for(int i = 0; i < 3; i++)
    {
        out << val[i];
    }
}

void IESerializeConverter::write(QDataStream& out, const glm::vec4& val)
{
    for(int i = 0; i < 4; i++)
    {
        out << val[i];
    }
}

void IESerializeConverter::write(QDataStream& out, const glm::mat2& val)
{
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            out << val[i][j];
        }
    }
}

void IESerializeConverter::write(QDataStream& out, const glm::mat3& val)
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            out << val[i][j];
        }
    }
}

void IESerializeConverter::write(QDataStream& out, const glm::mat4& val)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            out << val[i][j];
        }
    }
}

void IESerializeConverter::write(QDataStream& out, const GLSViewProjection& val)
{
    write(out, val.view);
    write(out, val.projection);
}

void IESerializeConverter::write(QDataStream& out, const GLSCamera& val)
{
    write(out, val.position);
    write(out, val.rotation);
}

void IESerializeConverter::write(QDataStream& out, const QVector<glm::vec2>& val)
{
    out << (int)val.size();

    foreach(auto& i, val)
    {
        IESerializeConverter::write(out, i);
    }
}

void IESerializeConverter::write(QDataStream& out, const QVector<glm::vec3>& val)
{
    out << (int)val.size();

    foreach(auto& i, val)
    {
        IESerializeConverter::write(out, i);
    }
}

void IESerializeConverter::write(QDataStream& out, const QVector<glm::vec4>& val)
{
    out << (int)val.size();

    foreach(auto& i, val)
    {
        IESerializeConverter::write(out, i);
    }
}

void IESerializeConverter::write(QDataStream& out, const QVector<glm::mat2>& val)
{
    out << (int)val.size();

    foreach(auto& i, val)
    {
        IESerializeConverter::write(out, i);
    }
}

void IESerializeConverter::write(QDataStream& out, const QVector<glm::mat3>& val)
{
    out << (int)val.size();

    foreach(auto& i, val)
    {
        IESerializeConverter::write(out, i);
    }
}

void IESerializeConverter::write(QDataStream& out, const QVector<glm::mat4>& val)
{
    out << (int)val.size();

    foreach(auto& i, val)
    {
        IESerializeConverter::write(out, i);
    }
}

void IESerializeConverter::write(QDataStream& out, const QVector<GLSViewProjection>& val)
{
    out << (int)val.size();

    foreach(auto& i, val)
    {
        IESerializeConverter::write(out, i);
    }
}

void IESerializeConverter::write(QDataStream& out, const QVector<GLSCamera>& val)
{
    out << (int)val.size();

    foreach(auto& i, val)
    {
        IESerializeConverter::write(out, i);
    }
}

void IESerializeConverter::read(QDataStream& in, std::any& val)
{
    size_t hashcode = 0;
    in >> hashcode;

    if(hashcode == hashcodes[0]) { glm::vec2 temp; read(in, temp); val = temp; }
    else if(hashcode == hashcodes[1]) { glm::vec3 temp; read(in, temp); val = temp; }
    else if(hashcode == hashcodes[2]) { glm::vec4 temp; read(in, temp); val = temp; }
    else if(hashcode == hashcodes[3]) { glm::mat4 temp; read(in, temp); val = temp; }
    else { char temp; in >> temp; val = temp; }
}

void IESerializeConverter::read(QDataStream& in, glm::vec2& val)
{
    for(int i = 0; i < 2; i++)
    {
        in >> val[i];
    }
}

void IESerializeConverter::read(QDataStream& in, glm::vec3& val)
{
    for(int i = 0; i < 3; i++)
    {
        in >> val[i];
    }
}

void IESerializeConverter::read(QDataStream& in, glm::vec4& val)
{
    for(int i = 0; i < 4; i++)
    {
        in >> val[i];
    }
}

void IESerializeConverter::read(QDataStream& in, glm::mat2& val)
{
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            in >> val[i][j];
        }
    }
}

void IESerializeConverter::read(QDataStream& in, glm::mat3& val)
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            in >> val[i][j];
        }
    }
}

void IESerializeConverter::read(QDataStream& in, glm::mat4& val)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            in >> val[i][j];
        }
    }
}

void IESerializeConverter::read(QDataStream& in, GLSViewProjection& val)
{
    read(in, val.view);
    read(in, val.projection);
}

void IESerializeConverter::read(QDataStream& in, GLSCamera& val)
{
    read(in, val.position);
    read(in, val.rotation);
}

void IESerializeConverter::read(QDataStream& in, QVector<glm::vec2>& val)
{
    val.clear();

    int count = 0;
    in >> count;

    for(int i = 0; i < count; i++)
    {
        glm::vec2 temp;
        IESerializeConverter::read(in, temp);
        val.append(temp);
    }
}

void IESerializeConverter::read(QDataStream& in, QVector<glm::vec3>& val)
{
    val.clear();

    int count = 0;
    in >> count;

    for(int i = 0; i < count; i++)
    {
        glm::vec3 temp;
        IESerializeConverter::read(in, temp);
        val.append(temp);
    }
}

void IESerializeConverter::read(QDataStream& in, QVector<glm::vec4>& val)
{
    val.clear();

    int count = 0;
    in >> count;

    for(int i = 0; i < count; i++)
    {
        glm::vec4 temp;
        IESerializeConverter::read(in, temp);
        val.append(temp);
    }
}

void IESerializeConverter::read(QDataStream& in, QVector<glm::mat2>& val)
{
    val.clear();

    int count = 0;
    in >> count;

    for(int i = 0; i < count; i++)
    {
        glm::mat2 temp;
        IESerializeConverter::read(in, temp);
        val.append(temp);
    }
}

void IESerializeConverter::read(QDataStream& in, QVector<glm::mat3>& val)
{
    val.clear();

    int count = 0;
    in >> count;

    for(int i = 0; i < count; i++)
    {
        glm::mat3 temp;
        IESerializeConverter::read(in, temp);
        val.append(temp);
    }
}

void IESerializeConverter::read(QDataStream& in, QVector<glm::mat4>& val)
{
    val.clear();

    int count = 0;
    in >> count;

    for(int i = 0; i < count; i++)
    {
        glm::mat4 temp;
        IESerializeConverter::read(in, temp);
        val.append(temp);
    }
}

void IESerializeConverter::read(QDataStream& in, QVector<GLSViewProjection>& val)
{
    val.clear();

    int count = 0;
    in >> count;

    for(int i = 0; i < count; i++)
    {
        GLSViewProjection temp;
        IESerializeConverter::read(in, temp);
        val.append(temp);
    }
}

void IESerializeConverter::read(QDataStream& in, QVector<GLSCamera>& val)
{
    val.clear();

    int count = 0;
    in >> count;

    for(int i = 0; i < count; i++)
    {
        GLSCamera temp;
        IESerializeConverter::read(in, temp);
        val.append(temp);
    }
}
