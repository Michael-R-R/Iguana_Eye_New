#include "IETexture2D.h"

IETexture2D::IETexture2D(QObject* parent) :
    QOpenGLTexture(Target::Target2D),
    IEFileResource(parent)
{

}

IETexture2D::IETexture2D(const QString& path,
                         Filter min, Filter mag,
                         WrapMode sWrap, WrapMode tWrap,
                         QObject* parent) :
    QOpenGLTexture(Target::Target2D),
    IEFileResource(path, parent)
{

    this->setMinificationFilter(min);
    this->setMagnificationFilter(mag);
    this->setWrapMode(QOpenGLTexture::DirectionS, sWrap);
    this->setWrapMode(QOpenGLTexture::DirectionT, tWrap);
}

IETexture2D::~IETexture2D()
{
    this->destroy();
}

bool IETexture2D::build()
{
    if(this->isCreated())
        this->destroy();

    if(!this->create())
        return false;

    this->bind();
    this->setData(QImage(this->name).mirrored());
    this->release();

    return true;
}

QDataStream& IETexture2D::serialize(QDataStream& out, const IESerializable& obj) const
{
    IEFileResource::serialize(out, obj);

    const auto& texture = static_cast<const IETexture2D&>(obj);

    out << texture.minificationFilter()
        << texture.magnificationFilter()
        << texture.wrapMode(QOpenGLTexture::DirectionS)
        << texture.wrapMode(QOpenGLTexture::DirectionT);

    return out;
}

QDataStream& IETexture2D::deserialize(QDataStream& in, IESerializable& obj)
{
    IEFileResource::deserialize(in, obj);

    auto& texture = static_cast<IETexture2D&>(obj);

    Filter min;
    Filter mag;
    WrapMode sWrap;
    WrapMode tWrap;

    in >> min
       >> mag
       >> sWrap
       >> tWrap;

    texture.setMinificationFilter(min);
    texture.setMagnificationFilter(mag);
    texture.setWrapMode(QOpenGLTexture::DirectionS, sWrap);
    texture.setWrapMode(QOpenGLTexture::DirectionT, tWrap);

    return in;
}
