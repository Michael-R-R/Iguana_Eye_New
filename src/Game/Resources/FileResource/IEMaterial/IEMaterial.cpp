#include "IEMaterial.h"
#include "IEShader.h"
#include "IESerialize.h"

IEMaterial::IEMaterial(QObject* parent) :
    IEFileResource(parent),
    colors(), textureIDs(), uData()
{
    setup();
}

IEMaterial::IEMaterial(const QString& path, QObject* parent) :
    IEFileResource(path, parent),
    colors(), textureIDs(), uData()
{
    setup();
}

IEMaterial::~IEMaterial()
{

}

void IEMaterial::appendColor(IEColorType type, const QVector4D& val)
{
    colors[type].append(val);
}

void IEMaterial::removeColor(IEColorType type, const int index)
{
    if(index < 0 || index > colors[type].size())
        return;

    colors[type].removeAt(index);
}

void IEMaterial::setColor(IEColorType type, const int index, const QVector4D& val)
{
    if(index < 0 || index > colors[type].size())
        return;

    colors[type][index] = val;
}

void IEMaterial::appendTextureID(IETextureType type, const uint64_t val)
{
    textureIDs[type].append(val);
}

void IEMaterial::removeTextureID(IETextureType type, const int index)
{
    if(index < 0 || index > textureIDs[type].size())
        return;

    textureIDs[type].removeAt(index);
}

void IEMaterial::setTextureID(IETextureType type, const int index, const uint64_t val)
{
    if(index < 0 || index > textureIDs[type].size())
        return;

    textureIDs[type][index] = val;
}

void IEMaterial::bindData(IEShader& shader) const
{
    uData.bind(shader);
}

const QHash<IEColorType, QVector<QVector4D> >& IEMaterial::getColors() const
{
    return colors;
}

const QHash<IETextureType, QVector<uint64_t> >& IEMaterial::getTexIDs() const
{
    return textureIDs;
}

IEUniformData& IEMaterial::getUniformData()
{
    return uData;
}

void IEMaterial::setUniformData(const IEUniformData& val)
{
    uData = val;
}

QDataStream& IEMaterial::serialize(QDataStream& out, const Serializable& obj) const
{
    IEFileResource::serialize(out, obj);

    const auto& material = static_cast<const IEMaterial&>(obj);

    out << material.colors << material.textureIDs << material.uData;

    return out;
}

QDataStream& IEMaterial::deserialize(QDataStream& in, Serializable& obj)
{
    IEFileResource::deserialize(in, obj);

    auto& material = static_cast<IEMaterial&>(obj);

    in >> material.colors >> material.textureIDs >> material.uData;

    return in;
}

void IEMaterial::setup()
{
    colors.insert(IEColorType::Ambient, QVector<QVector4D>());
    colors.insert(IEColorType::Diffuse, QVector<QVector4D>());
    colors.insert(IEColorType::Specular, QVector<QVector4D>());
    colors.insert(IEColorType::Emissive, QVector<QVector4D>());
    colors.insert(IEColorType::Reflective, QVector<QVector4D>());
    colors.insert(IEColorType::Transparent, QVector<QVector4D>());

    textureIDs.insert(IETextureType::Ambient, QVector<uint64_t>());
    textureIDs.insert(IETextureType::Diffuse, QVector<uint64_t>());
    textureIDs.insert(IETextureType::Specular, QVector<uint64_t>());
    textureIDs.insert(IETextureType::Normals, QVector<uint64_t>());
    textureIDs.insert(IETextureType::Height, QVector<uint64_t>());
    textureIDs.insert(IETextureType::Emissive, QVector<uint64_t>());
    textureIDs.insert(IETextureType::Shininess, QVector<uint64_t>());
    textureIDs.insert(IETextureType::Opacity, QVector<uint64_t>());
    textureIDs.insert(IETextureType::Displacement, QVector<uint64_t>());
    textureIDs.insert(IETextureType::Lightmap, QVector<uint64_t>());
    textureIDs.insert(IETextureType::Unknown, QVector<uint64_t>());
}
