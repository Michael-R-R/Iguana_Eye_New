#include "IEUniformData.h"
#include "IEShader.h"

IEUniformData::IEUniformData() :
    intData(), floatData(),
    vec2Data(), vec3Data(),
    vec4Data(), mat2Data(),
    mat3Data(), mat4Data(),
    colData()
{

}

IEUniformData::IEUniformData(const IEUniformData& other) :
    intData(other.intData), floatData(other.floatData),
    vec2Data(other.vec2Data), vec3Data(other.vec3Data),
    vec4Data(other.vec4Data), mat2Data(other.mat2Data),
    mat3Data(other.mat3Data), mat4Data(other.mat4Data),
    colData(other.colData)
{

}

IEUniformData::~IEUniformData()
{

}

void IEUniformData::bind(IEShader& shader) const
{
    QMapIterator<QString, int> it1(intData);
    while(it1.hasNext()) { it1.next(); shader.setUniformValue(shader.uniformLocation(it1.key()), it1.value()); }

    QMapIterator<QString, float> it2(floatData);
    while(it2.hasNext()) { it2.next(); shader.setUniformValue(shader.uniformLocation(it2.key()), it2.value()); }

    QMapIterator<QString, QVector2D> it3(vec2Data);
    while(it3.hasNext()) { it3.next(); shader.setUniformValue(shader.uniformLocation(it3.key()), it3.value()); }

    QMapIterator<QString, QVector3D> it4(vec3Data);
    while(it4.hasNext()) { it4.next(); shader.setUniformValue(shader.uniformLocation(it4.key()), it4.value()); }

    QMapIterator<QString, QVector4D> it5(vec4Data);
    while(it5.hasNext()) { it5.next(); shader.setUniformValue(shader.uniformLocation(it5.key()), it5.value()); }

    QMapIterator<QString, QMatrix2x2> it6(mat2Data);
    while(it6.hasNext()) { it6.next(); shader.setUniformValue(shader.uniformLocation(it6.key()), it6.value()); }

    QMapIterator<QString, QMatrix3x3> it7(mat3Data);
    while(it7.hasNext()) { it7.next(); shader.setUniformValue(shader.uniformLocation(it7.key()), it7.value()); }

    QMapIterator<QString, QMatrix4x4> it8(mat4Data);
    while(it8.hasNext()) { it8.next(); shader.setUniformValue(shader.uniformLocation(it8.key()), it8.value()); }

    QMapIterator<QString, QColor> it9(colData);
    while(it9.hasNext()) { it9.next(); shader.setUniformValue(shader.uniformLocation(it9.key()), it9.value()); }
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

void IEUniformData::add(const QString& name, const QVector2D data)
{
    if(name.isEmpty())
        return;
    vec2Data[name] = data;
}

void IEUniformData::add(const QString& name, const QVector3D data)
{
    if(name.isEmpty())
        return;
    vec3Data[name] = data;
}

void IEUniformData::add(const QString& name, const QVector4D data)
{
    if(name.isEmpty())
        return;
    vec4Data[name] = data;
}

void IEUniformData::add(const QString& name, const QMatrix2x2 data)
{
    if(name.isEmpty())
        return;
    mat2Data[name] = data;
}

void IEUniformData::add(const QString& name, const QMatrix3x3 data)
{
    if(name.isEmpty())
        return;
    mat3Data[name] = data;
}

void IEUniformData::add(const QString& name, const QMatrix4x4 data)
{
    if(name.isEmpty())
        return;
    mat4Data[name] = data;
}

void IEUniformData::add(const QString& name, const QColor data)
{
    if(name.isEmpty())
        return;
    colData[name] = data;
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

void IEUniformData::removeCol(const QString& name)
{
    colData.remove(name);
}

QDataStream& IEUniformData::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& uniform = static_cast<const IEUniformData&>(obj);

    out << uniform.intData << uniform.floatData
        << uniform.vec2Data << uniform.vec3Data
        << uniform.vec4Data << uniform.mat2Data
        << uniform.mat3Data << uniform.mat4Data
        << uniform.colData;

    return out;
}

QDataStream& IEUniformData::deserialize(QDataStream& in, Serializable& obj)
{
    auto& uniform = static_cast<IEUniformData&>(obj);

    in >> uniform.intData >> uniform.floatData >> uniform.vec2Data
       >> uniform.vec3Data >> uniform.vec4Data >> uniform.mat2Data
       >> uniform.mat3Data >> uniform.mat4Data >> uniform.colData;

    return in;
}
