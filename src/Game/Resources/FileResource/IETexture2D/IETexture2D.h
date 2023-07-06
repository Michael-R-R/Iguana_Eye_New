#pragma once

#include <QOpenGLTexture>

#include "IEFileResource.h"

class IETexture2D : public QOpenGLTexture, public IEFileResource
{
public:
    IETexture2D(QObject* parent = nullptr);
    IETexture2D(const QString& path,
                Filter min, Filter mag,
                WrapMode sWrap, WrapMode tWrap,
                QObject* parent = nullptr);
    virtual ~IETexture2D();

    bool build();

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};

