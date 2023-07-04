#include "IEMaterial.h"
#include "IEShader.h"
#include "IESerialize.h"

IEMaterial::IEMaterial(QObject* parent) :
    IEFileResource(parent),
    colorNames(),
    colors(), textureIDs(),
    children(), materials()
{
    setup();
}

IEMaterial::IEMaterial(const QString& path, QObject* parent) :
    IEFileResource(path, parent),
    colorNames(),
    colors(), textureIDs(),
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
    colors[type] = val;
}

void IEMaterial::removeColor(IEColorType type)
{
    colors[type] = QVector4D{};
}

void IEMaterial::setTextureID(IETextureType type, const uint64_t val)
{
    textureIDs[type] = val;
}

void IEMaterial::removeTextureID(IETextureType type)
{
    textureIDs[type] = 0;
}

QDataStream& IEMaterial::serialize(QDataStream& out, const Serializable& obj) const
{
    IEFileResource::serialize(out, obj);

    const auto& material = static_cast<const IEMaterial&>(obj);

    out << material.colors << material.textureIDs;

    return out;
}

QDataStream& IEMaterial::deserialize(QDataStream& in, Serializable& obj)
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

    colors.insert(IEColorType::Ambient, QVector4D{});
    colors.insert(IEColorType::Diffuse, QVector4D{});
    colors.insert(IEColorType::Specular, QVector4D{});
    colors.insert(IEColorType::Emissive, QVector4D{});
    colors.insert(IEColorType::Reflective, QVector4D{});
    colors.insert(IEColorType::Transparent, QVector4D{});

    textureIDs.insert(IETextureType::Ambient, 0);
    textureIDs.insert(IETextureType::Diffuse, 0);
    textureIDs.insert(IETextureType::Specular, 0);
    textureIDs.insert(IETextureType::Normals, 0);
    textureIDs.insert(IETextureType::Height, 0);
    textureIDs.insert(IETextureType::Emissive, 0);
    textureIDs.insert(IETextureType::Shininess, 0);
    textureIDs.insert(IETextureType::Opacity, 0);
    textureIDs.insert(IETextureType::Displacement, 0);
    textureIDs.insert(IETextureType::Lightmap, 0);
    textureIDs.insert(IETextureType::Unknown, 0);
}
