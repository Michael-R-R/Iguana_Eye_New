#include "IESerializeConverter.h"

void IESerializeConverter::write(QDataStream& out, const std::any& val)
{
    size_t hashcode = val.type().hash_code();

    if(hashcode == hashcodes[0]) { out << hashcode << std::any_cast<QVector2D>(val); }
    else if(hashcode == hashcodes[1]) { out << hashcode << std::any_cast<QVector3D>(val); }
    else if(hashcode == hashcodes[2]) { out << hashcode << std::any_cast<QVector4D>(val); }
    else if(hashcode == hashcodes[3]) { out << hashcode << std::any_cast<QMatrix4x4>(val); }
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

void IESerializeConverter::write(QDataStream& out, const QVector<glm::vec2>& val)
{
    foreach(auto& i, val)
    {
        IESerializeConverter::write(out, i);
    }
}

void IESerializeConverter::write(QDataStream& out, const QVector<glm::vec3>& val)
{
    foreach(auto& i, val)
    {
        IESerializeConverter::write(out, i);
    }
}

void IESerializeConverter::write(QDataStream& out, const QVector<glm::vec4>& val)
{
    foreach(auto& i, val)
    {
        IESerializeConverter::write(out, i);
    }
}

void IESerializeConverter::write(QDataStream& out, const QVector<glm::mat2>& val)
{
    foreach(auto& i, val)
    {
        IESerializeConverter::write(out, i);
    }
}

void IESerializeConverter::write(QDataStream& out, const QVector<glm::mat3>& val)
{
    foreach(auto& i, val)
    {
        IESerializeConverter::write(out, i);
    }
}

void IESerializeConverter::write(QDataStream& out, const QVector<glm::mat4>& val)
{
    foreach(auto& i, val)
    {
        IESerializeConverter::write(out, i);
    }
}

void IESerializeConverter::read(QDataStream& in, std::any& val)
{
    size_t hashcode = 0;
    in >> hashcode;

    if(hashcode == hashcodes[0]) { QVector2D temp; in >> temp; val = temp; }
    else if(hashcode == hashcodes[1]) { QVector3D temp; in >> temp; val = temp; }
    else if(hashcode == hashcodes[2]) { QVector4D temp; in >> temp; val = temp; }
    else if(hashcode == hashcodes[3]) { QMatrix4x4 temp; in >> temp; val = temp; }
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

void IESerializeConverter::read(QDataStream& in, QVector<glm::vec2>& val)
{
    for(int i = 0; i < val.size(); i++)
    {
        IESerializeConverter::read(in, val[i]);
    }
}

void IESerializeConverter::read(QDataStream& in, QVector<glm::vec3>& val)
{
    for(int i = 0; i < val.size(); i++)
    {
        IESerializeConverter::read(in, val[i]);
    }
}

void IESerializeConverter::read(QDataStream& in, QVector<glm::vec4>& val)
{
    for(int i = 0; i < val.size(); i++)
    {
        IESerializeConverter::read(in, val[i]);
    }
}

void IESerializeConverter::read(QDataStream& in, QVector<glm::mat2>& val)
{
    for(int i = 0; i < val.size(); i++)
    {
        IESerializeConverter::read(in, val[i]);
    }
}

void IESerializeConverter::read(QDataStream& in, QVector<glm::mat3>& val)
{
    for(int i = 0; i < val.size(); i++)
    {
        IESerializeConverter::read(in, val[i]);
    }
}

void IESerializeConverter::read(QDataStream& in, QVector<glm::mat4>& val)
{
    for(int i = 0; i < val.size(); i++)
    {
        IESerializeConverter::read(in, val[i]);
    }
}
