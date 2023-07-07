#pragma once

#include <QMatrix4x4>

#include "IESerializable.h"

struct GLViewProjectionStruct : public IESerializable
{
    QMatrix4x4 view;
    QMatrix4x4 projection;
    QMatrix4x4 viewProjection;

    GLViewProjectionStruct() :
        view(),
        projection(),
        viewProjection()
    {

    }

    GLViewProjectionStruct(const QMatrix4x4& view, const QMatrix4x4& projection) :
        view(view),
        projection(projection),
        viewProjection(view * projection)
    {

    }

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override
    {
        const auto& data = static_cast<const GLViewProjectionStruct&>(obj);

        out << data.view << data.projection;

        return out;
    }

    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override
    {
        auto& data = static_cast<GLViewProjectionStruct&>(obj);

        in >> data.view >> data.projection;

        data.viewProjection = data.view * data.projection;

        return in;
    }
};

