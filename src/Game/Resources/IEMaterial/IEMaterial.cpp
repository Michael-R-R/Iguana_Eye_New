#include "IEMaterial.h"
#include "IEShader.h"

IEMaterial::IEMaterial() :
    IEResource("", 0),
    uniformData(), objectColor(),
    atlasTexId(0), diffuseTexId(0),
    specularTexId(0), normalTexId(0),
    heightTexId(0), isEdited(false)
{

}

IEMaterial::IEMaterial(const QString& path, const unsigned long long id) :
    IEResource(path, id),
    uniformData(), objectColor(),
    atlasTexId(0), diffuseTexId(0),
    specularTexId(0), normalTexId(0),
    heightTexId(0), isEdited(true)
{

}

IEMaterial::IEMaterial(const IEMaterial& other) :
    IEResource(other.filePath, other.id),
    uniformData(other.uniformData), objectColor(other.objectColor),
    atlasTexId(other.atlasTexId), diffuseTexId(other.diffuseTexId),
    specularTexId(other.specularTexId), normalTexId(other.normalTexId),
    heightTexId(other.heightTexId), isEdited(other.isEdited)
{

}

IEMaterial::~IEMaterial()
{

}

void IEMaterial::bindUniformData(IEShader& shader) const
{
    uniformData.bind(shader);
}

QDataStream& IEMaterial::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& material = static_cast<const IEMaterial&>(obj);

    out << material.filePath
        << material.id
        << material.uniformData
        << material.objectColor
        << material.atlasTexId
        << material.diffuseTexId
        << material.specularTexId
        << material.normalTexId
        << material.heightTexId
        << material.isEdited;

    return out;
}

QDataStream& IEMaterial::deserialize(QDataStream& in, Serializable& obj)
{
    auto& material = static_cast<IEMaterial&>(obj);

    in >> material.filePath
       >> material.id
       >> material.uniformData
       >> material.objectColor
       >> material.atlasTexId
       >> material.diffuseTexId
       >> material.specularTexId
       >> material.normalTexId
       >> material.heightTexId
       >> material.isEdited;

    return in;
}
