#pragma once

#include <QOpenGLTexture>

#include "IEFileResource.h"

class IETexture2D : public QOpenGLTexture, public IEFileResource
{
protected:
    QString imgPath;

public:
    IETexture2D(QObject* parent = nullptr);
    IETexture2D(const QString& path,
                const QString& imgPath,
                Filter min, Filter mag,
                WrapMode sWrap, WrapMode tWrap,
                QObject* parent = nullptr);
    virtual ~IETexture2D();

    bool build();

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};

