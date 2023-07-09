#include "IEUniformData.h"
#include "IEShader.h"
#include "IESerializeConverter.h"

IEUniformData::IEUniformData() :
    intData(), floatData(),
    vec2Data(), vec3Data(),
    vec4Data(), mat2Data(),
    mat3Data(), mat4Data()
{

}

IEUniformData::IEUniformData(const IEUniformData& other) :
    intData(other.intData), floatData(other.floatData),
    vec2Data(other.vec2Data), vec3Data(other.vec3Data),
    vec4Data(other.vec4Data), mat2Data(other.mat2Data),
    mat3Data(other.mat3Data), mat4Data(other.mat4Data)
{

}

IEUniformData::~IEUniformData()
{

}

void IEUniformData::bind(IEShader& shader) const
{
    QMapIterator<QString, int> it1(intData);
    while(it1.hasNext()) { it1.next(); shader.setInt(it1.key().toLocal8Bit().data(), it1.value()); }

    QMapIterator<QString, float> it2(floatData);
    while(it2.hasNext()) { it2.next(); shader.setFloat(it2.key().toLocal8Bit().data(), it2.value()); }

    QMapIterator<QString, glm::vec2> it3(vec2Data);
    while(it3.hasNext()) { it3.next(); shader.setVec2(it3.key().toLocal8Bit().data(), it3.value()); }

    QMapIterator<QString, glm::vec3> it4(vec3Data);
    while(it4.hasNext()) { it4.next(); shader.setVec3(it4.key().toLocal8Bit().data(), it4.value()); }

    QMapIterator<QString, glm::vec4> it5(vec4Data);
    while(it5.hasNext()) { it5.next(); shader.setVec4(it5.key().toLocal8Bit().data(), it5.value()); }

    QMapIterator<QString, glm::mat2> it6(mat2Data);
    while(it6.hasNext()) { it6.next(); shader.setMat2(it6.key().toLocal8Bit().data(), it6.value()); }

    QMapIterator<QString, glm::mat3> it7(mat3Data);
    while(it7.hasNext()) { it7.next(); shader.setMat3(it7.key().toLocal8Bit().data(), it7.value()); }

    QMapIterator<QString, glm::mat4> it8(mat4Data);
    while(it8.hasNext()) { it8.next(); shader.setMat4(it8.key().toLocal8Bit().data(), it8.value()); }
}

void IEUniformData::add(const QString& name, const int data)
{
    if(name.isEmpty())
        return;
    intData[name] = data;
}

void IEUniformData::add(const QString& name, const float data)
{
    if(name.isEmpty())
        return;
    floatData[name] = data;
}

void IEUniformData::add(const QString& name, const glm::vec2 data)
{
    if(name.isEmpty())
        return;
    vec2Data[name] = data;
}

void IEUniformData::add(const QString& name, const glm::vec3 data)
{
    if(name.isEmpty())
        return;
    vec3Data[name] = data;
}

void IEUniformData::add(const QString& name, const glm::vec4 data)
{
    if(name.isEmpty())
        return;
    vec4Data[name] = data;
}

void IEUniformData::add(const QString& name, const glm::mat2 data)
{
    if(name.isEmpty())
        return;
    mat2Data[name] = data;
}

void IEUniformData::add(const QString& name, const glm::mat3 data)
{
    if(name.isEmpty())
        return;
    mat3Data[name] = data;
}

void IEUniformData::add(const QString& name, const glm::mat4 data)
{
    if(name.isEmpty())
        return;
    mat4Data[name] = data;
}

void IEUniformData::removeInt(const QString& name)
{
    intData.remove(name);
}

void IEUniformData::removeFloat(const QString& name)
{
    floatData.remove(name);
}

void IEUniformData::removeVec2(const QString& name)
{
    vec2Data.remove(name);
}

void IEUniformData::removeVec3(const QString& name)
{
    vec3Data.remove(name);
}

void IEUniformData::removeVec4(const QString& name)
{
    vec4Data.remove(name);
}

void IEUniformData::removeMat2(const QString& name)
{
    mat2Data.remove(name);
}

void IEUniformData::removeMat3(const QString& name)
{
    mat3Data.remove(name);
}

void IEUniformData::removeMat4(const QString& name)
{
    mat4Data.remove(name);
}

QDataStream& IEUniformData::serialize(QDataStream& out, const IESerializable& obj) const
{
    const auto& uniform = static_cast<const IEUniformData&>(obj);

    // TODO implement converters

    return out;
}

QDataStream& IEUniformData::deserialize(QDataStream& in, IESerializable& obj)
{
    auto& uniform = static_cast<IEUniformData&>(obj);

    // TODO implement converters

    return in;
}
