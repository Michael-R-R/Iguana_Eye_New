#pragma once

#include <QDataStream>
#include <QHash>
#include <any>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>

class IESerializeTranslator
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
    static std::any read(QDataStream& in);
};

