#pragma once

#include <QDataStream>
#include <QHash>
#include <any>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>
#include <glm/glm.hpp>

class IESerializeConverter
{
    static inline QHash<unsigned, size_t> hashcodes
    {
            { 0, typeid(QVector2D).hash_code() },
            { 1, typeid(QVector3D).hash_code() },
            { 2, typeid(QVector4D).hash_code() },
            { 3, typeid(QMatrix4x4).hash_code() },
    };

public:
    static void write(QDataStream& out, const std::any& val);
    static void write(QDataStream& out, const glm::vec2& val);
    static void write(QDataStream& out, const glm::vec3& val);
    static void write(QDataStream& out, const glm::vec4& val);
    static void write(QDataStream& out, const glm::mat2& val);
    static void write(QDataStream& out, const glm::mat3& val);
    static void write(QDataStream& out, const glm::mat4& val);
    static void write(QDataStream& out, const QVector<glm::vec2>& val);
    static void write(QDataStream& out, const QVector<glm::vec3>& val);
    static void write(QDataStream& out, const QVector<glm::vec4>& val);
    static void write(QDataStream& out, const QVector<glm::mat2>& val);
    static void write(QDataStream& out, const QVector<glm::mat3>& val);
    static void write(QDataStream& out, const QVector<glm::mat4>& val);

    static void read(QDataStream& in, std::any& val);
    static void read(QDataStream& in, glm::vec2& val);
    static void read(QDataStream& in, glm::vec3& val);
    static void read(QDataStream& in, glm::vec4& val);
    static void read(QDataStream& in, glm::mat2& val);
    static void read(QDataStream& in, glm::mat3& val);
    static void read(QDataStream& in, glm::mat4& val);
    static void read(QDataStream& in, QVector<glm::vec2>& val);
    static void read(QDataStream& in, QVector<glm::vec3>& val);
    static void read(QDataStream& in, QVector<glm::vec4>& val);
    static void read(QDataStream& in, QVector<glm::mat2>& val);
    static void read(QDataStream& in, QVector<glm::mat3>& val);
    static void read(QDataStream& in, QVector<glm::mat4>& val);
};

