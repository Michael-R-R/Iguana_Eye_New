#pragma once

#include <QDataStream>

#include <QMap>
#include <QString>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QMatrix2x2>
#include <QMatrix3x3>
#include <QMatrix4x4>
#include <QColor>

class IEShader;

class IEUniform
{
    QMap<QString, int> intData;
    QMap<QString, float> floatData;
    QMap<QString, QVector2D> vec2Data;
    QMap<QString, QVector3D> vec3Data;
    QMap<QString, QVector4D> vec4Data;
    QMap<QString, QMatrix2x2> mat2Data;
    QMap<QString, QMatrix3x3> mat3Data;
    QMap<QString, QMatrix4x4> mat4Data;
    QMap<QString, QColor> colData;

public:
    IEUniform();
    IEUniform(const IEUniform& other);
    ~IEUniform();

    void bind(IEShader* shader);

    void add(const QString& name, const int data);
    void add(const QString& name, const float data);
    void add(const QString& name, const QVector2D data);
    void add(const QString& name, const QVector3D data);
    void add(const QString& name, const QVector4D data);
    void add(const QString& name, const QMatrix2x2 data);
    void add(const QString& name, const QMatrix3x3 data);
    void add(const QString& name, const QMatrix4x4 data);
    void add(const QString& name, const QColor data);

    void removeInt(const QString& name);
    void removeFloat(const QString& name);
    void removeVec2(const QString& name);
    void removeVec3(const QString& name);
    void removeVec4(const QString& name);
    void removeMat2(const QString& name);
    void removeMat3(const QString& name);
    void removeMat4(const QString& name);
    void removeCol(const QString& name);

    const QMap<QString, int>& getIntData() const { return intData; }
    const QMap<QString, float>& getFloatData() const { return floatData; }
    const QMap<QString, QVector2D>& getVec2Data() const { return vec2Data; }
    const QMap<QString, QVector3D>& getVec3Data() const { return vec3Data; }
    const QMap<QString, QVector4D>& getVec4Data() const { return vec4Data; }
    const QMap<QString, QMatrix2x2>& getMat2Data() const { return mat2Data; }
    const QMap<QString, QMatrix3x3>& getMat3Data() const { return mat3Data; }
    const QMap<QString, QMatrix4x4>& getMat4Data() const { return mat4Data; }
    const QMap<QString, QColor>& getColData() const { return colData; }

    void setIntData(const QMap<QString, int>& val) { intData = val; }
    void setFloatData(const QMap<QString, float>& val) { floatData = val; }
    void setVec2Data(const QMap<QString, QVector2D>& val) { vec2Data = val; }
    void setVec3Data(const QMap<QString, QVector3D>& val) { vec3Data = val; }
    void setVec4Data(const QMap<QString, QVector4D>& val) { vec4Data = val; }
    void setMat2Data(const QMap<QString, QMatrix2x2>& val) { mat2Data = val; }
    void setMat3Data(const QMap<QString, QMatrix3x3>& val) { mat3Data = val; }
    void setMat4Data(const QMap<QString, QMatrix4x4>& val) { mat4Data = val; }
    void setColData(const QMap<QString, QColor>& val) { colData = val; }
};

QDataStream& operator<<(QDataStream& out, const IEUniform& uniform);
QDataStream& operator>>(QDataStream& in, IEUniform& uniform);
