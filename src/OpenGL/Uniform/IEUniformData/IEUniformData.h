#pragma once

#include <QMap>
#include <QString>
#include <glm/glm.hpp>

#include "IESerializable.h"
#include "IESerializeConverter.h"

class IEShader;

class IEUniformData : public IESerializable
{
    QMap<QString, int> intData;
    QMap<QString, float> floatData;
    QMap<QString, glm::vec2> vec2Data;
    QMap<QString, glm::vec3> vec3Data;
    QMap<QString, glm::vec4> vec4Data;
    QMap<QString, glm::mat2> mat2Data;
    QMap<QString, glm::mat3> mat3Data;
    QMap<QString, glm::mat4> mat4Data;

public:
    IEUniformData();
    IEUniformData(const IEUniformData& other);
    ~IEUniformData();

    void bind(IEShader& shader) const;
    void clear();

    void add(const QString& name, const int data);
    void add(const QString& name, const float data);
    void add(const QString& name, const glm::vec2 data);
    void add(const QString& name, const glm::vec3 data);
    void add(const QString& name, const glm::vec4 data);
    void add(const QString& name, const glm::mat2 data);
    void add(const QString& name, const glm::mat3 data);
    void add(const QString& name, const glm::mat4 data);

    void removeInt(const QString& name);
    void removeFloat(const QString& name);
    void removeVec2(const QString& name);
    void removeVec3(const QString& name);
    void removeVec4(const QString& name);
    void removeMat2(const QString& name);
    void removeMat3(const QString& name);
    void removeMat4(const QString& name);

    const QMap<QString, int>& getIntData() const { return intData; }
    const QMap<QString, float>& getFloatData() const { return floatData; }
    const QMap<QString, glm::vec2>& getVec2Data() const { return vec2Data; }
    const QMap<QString, glm::vec3>& getVec3Data() const { return vec3Data; }
    const QMap<QString, glm::vec4>& getVec4Data() const { return vec4Data; }
    const QMap<QString, glm::mat2>& getMat2Data() const { return mat2Data; }
    const QMap<QString, glm::mat3>& getMat3Data() const { return mat3Data; }
    const QMap<QString, glm::mat4>& getMat4Data() const { return mat4Data; }

    void setIntData(const QMap<QString, int>& val) { intData = val; }
    void setFloatData(const QMap<QString, float>& val) { floatData = val; }
    void setVec2Data(const QMap<QString, glm::vec2>& val) { vec2Data = val; }
    void setVec3Data(const QMap<QString, glm::vec3>& val) { vec3Data = val; }
    void setVec4Data(const QMap<QString, glm::vec4>& val) { vec4Data = val; }
    void setMat2Data(const QMap<QString, glm::mat2>& val) { mat2Data = val; }
    void setMat3Data(const QMap<QString, glm::mat3>& val) { mat3Data = val; }
    void setMat4Data(const QMap<QString, glm::mat4>& val) { mat4Data = val; }

    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;

private:
    template<class T>
    void serializeHelper(QDataStream& out, const QMap<QString, T>& map) const
    {
        out << (int)map.size();

        QMapIterator<QString, T> it(map);
        while(it.hasNext())
        {
            it.next();

            out << it.key();
            IESerializeConverter::write(out, it.value());
        }
    }

    template<class T>
    void deserializeHelper(QDataStream &in, QMap<QString, T>& map)
    {
        int count = 0;

        in >> count;

        for(int i = 0; i < count; i++)
        {
            QString name;
            T temp;

            in >> name;
            IESerializeConverter::read(in, temp);

            map.insert(name, temp);
        }
    }
};
