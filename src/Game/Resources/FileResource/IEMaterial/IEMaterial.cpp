#include "IEMaterial.h"
#include "IEShader.h"
#include "IETexture2D.h"
#include "IETexture2DManager.h"
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

void IEMaterial::bindTextures(IEShader& shader, IETexture2DManager& manager)
{
    int counter = 0;

    QHashIterator<IETextureType, QVector<uint64_t>> it(textureIDs);
    while(it.hasNext())
    {
        it.next();

        const QVector<uint64_t>& values = it.value();
        for(int i = 0; i < values.size(); i++)
        {
            QString name = QString("%1_%2").arg(textureNames[it.key()], QString::number(i));
            QByteArray temp = name.toLocal8Bit();
            shader.setUniformValue(temp.data(), counter);

            auto* texture = manager.value<IETexture2D>(values[i]);
            if(!texture)
            {
                continue;
            }

            texture->bind(counter);

            counter++;
        }
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

void IEMaterial::appendTextureID(IETextureType type, const uint64_t val)
{
    textureIDs[type].append(val);
}

void IEMaterial::setTextureID(IETextureType type, const int index, const uint64_t val)
{
    if(index < 0 || index >= textureIDs[type].size())
        return;

    textureIDs[type][index] = val;
}

void IEMaterial::removeTextureID(IETextureType type, const int index)
{
    if(index < 0 || index >= textureIDs[type].size())
        return;

    textureIDs[type].removeAt(index);
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
    textureIDs.insert(IETextureType::Ambient, QVector<uint64_t>{});
    textureIDs.insert(IETextureType::Diffuse, QVector<uint64_t>{});
    textureIDs.insert(IETextureType::Specular, QVector<uint64_t>{});
    textureIDs.insert(IETextureType::Normals, QVector<uint64_t>{});
    textureIDs.insert(IETextureType::Height, QVector<uint64_t>{});
    textureIDs.insert(IETextureType::Emissive, QVector<uint64_t>{});
    textureIDs.insert(IETextureType::Shininess, QVector<uint64_t>{});
    textureIDs.insert(IETextureType::Opacity, QVector<uint64_t>{});
    textureIDs.insert(IETextureType::Displacement, QVector<uint64_t>{});
    textureIDs.insert(IETextureType::Lightmap, QVector<uint64_t>{});
    textureIDs.insert(IETextureType::Unknown, QVector<uint64_t>{});

    colorNames.insert(IEColorType::Ambient, "uc_ambient");
    colorNames.insert(IEColorType::Diffuse, "uc_diffuse");
    colorNames.insert(IEColorType::Specular, "uc_specular");
    colorNames.insert(IEColorType::Emissive, "uc_emissive");
    colorNames.insert(IEColorType::Reflective, "uc_reflective");
    colorNames.insert(IEColorType::Transparent, "uc_transparent");

    textureNames.insert(IETextureType::Ambient, "ut_ambient");
    textureNames.insert(IETextureType::Diffuse, "ut_diffuse");
    textureNames.insert(IETextureType::Specular, "ut_specular");
    textureNames.insert(IETextureType::Normals, "ut_normal");
    textureNames.insert(IETextureType::Height, "ut_height");
    textureNames.insert(IETextureType::Emissive, "ut_emissive");
    textureNames.insert(IETextureType::Shininess, "ut_shininess");
    textureNames.insert(IETextureType::Opacity, "ut_opacity");
    textureNames.insert(IETextureType::Displacement, "ut_displacement");
    textureNames.insert(IETextureType::Lightmap, "ut_lightmap");
    textureNames.insert(IETextureType::Unknown, "ut_unknown");
}
