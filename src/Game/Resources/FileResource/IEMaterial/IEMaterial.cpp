#include "IEMaterial.h"
#include "IEShader.h"
#include "IESerialize.h"

IEMaterial::IEMaterial(QObject* parent) :
    IEFileResource(parent),
    colors(), textureIDs(),
    colorNames(), textureNames(),
    children(), materials()
{
    setup();
}

IEMaterial::IEMaterial(const QString& path, QObject* parent) :
    IEFileResource(path, parent),
    colors(), textureIDs(),
    colorNames(), textureNames(),
    children(), materials()
{
    setup();
}

IEMaterial::~IEMaterial()
{

}

void IEMaterial::bindColors(IEShader& shader)
{
    QHashIterator<IEColorType, QVector4D> it(colors);
    while(it.hasNext())
    {
        it.next();
        shader.setUniformValue(colorNames[it.key()], it.value());
    }
}

void IEMaterial::setColor(IEColorType type, const QVector4D& val)
{
    colors.insert(type, val);
}

void IEMaterial::removeColor(IEColorType type)
{
    colors.remove(type);
}

void IEMaterial::setTextureID(IETextureType type, const uint64_t val)
{
    textureIDs.insert(type, val);
}

void IEMaterial::removeTextureID(IETextureType type)
{
    textureIDs.remove(type);
}

QDataStream& IEMaterial::serialize(QDataStream& out, const IESerializable& obj) const
{
    IEFileResource::serialize(out, obj);

    const auto& material = static_cast<const IEMaterial&>(obj);

    out << material.colors << material.textureIDs;

    return out;
}

QDataStream& IEMaterial::deserialize(QDataStream& in, IESerializable& obj)
{
    IEFileResource::deserialize(in, obj);

    auto& material = static_cast<IEMaterial&>(obj);

    in >> material.colors >> material.textureIDs;

    return in;
}

void IEMaterial::setup()
{
    colorNames.insert(IEColorType::Ambient, "uColor0");
    colorNames.insert(IEColorType::Diffuse, "uColor1");
    colorNames.insert(IEColorType::Specular, "uColor2");
    colorNames.insert(IEColorType::Emissive, "uColor3");
    colorNames.insert(IEColorType::Reflective, "uColor4");
    colorNames.insert(IEColorType::Transparent, "uColor5");

    textureNames.insert(IETextureType::Ambient, "uTexture0");
    textureNames.insert(IETextureType::Diffuse, "uTexture1");
    textureNames.insert(IETextureType::Specular, "uTexture2");
    textureNames.insert(IETextureType::Normals, "uTexture3");
    textureNames.insert(IETextureType::Height, "uTexture4");
    textureNames.insert(IETextureType::Emissive, "uTexture5");
    textureNames.insert(IETextureType::Shininess, "uTexture6");
    textureNames.insert(IETextureType::Opacity, "uTexture7");
    textureNames.insert(IETextureType::Displacement, "uTexture8");
    textureNames.insert(IETextureType::Lightmap, "uTexture9");
    textureNames.insert(IETextureType::Unknown, "uTexture10");
}
