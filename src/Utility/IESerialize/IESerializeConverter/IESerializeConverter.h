#pragma once

#include <QDataStream>
#include <QHash>
#include <any>
#include <glm/glm.hpp>

class IESerializeConverter
{
    static inline QHash<unsigned, size_t> hashcodes
    {
            { 0, typeid(glm::vec2).hash_code() },
            { 1, typeid(glm::vec3).hash_code() },
            { 2, typeid(glm::vec4).hash_code() },
            { 3, typeid(glm::mat4).hash_code() },
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

