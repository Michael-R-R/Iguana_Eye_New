#include "IEMaterial.h"
#include "IEShader.h"
#include "IESerialize.h"

IEMaterial::IEMaterial(QObject* parent) :
    IEResource(parent),
    uniformData(), objectColor(),
    atlasTexId(0), diffuseTexId(0),
    specularTexId(0), normalTexId(0),
    heightTexId(0)
{

}

IEMaterial::IEMaterial(const QString& path, QObject* parent) :
    IEResource(path, parent),
    uniformData(), objectColor(),
    atlasTexId(0), diffuseTexId(0),
    specularTexId(0), normalTexId(0),
    heightTexId(0)
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
    IEResource::serialize(out, obj);

    const auto& material = static_cast<const IEMaterial&>(obj);

    out << material.uniformData
        << material.objectColor
        << material.atlasTexId
        << material.diffuseTexId
        << material.specularTexId
        << material.normalTexId
        << material.heightTexId;

    return out;
}

QDataStream& IEMaterial::deserialize(QDataStream& in, Serializable& obj)
{
    IEResource::deserialize(in, obj);

    auto& material = static_cast<IEMaterial&>(obj);

    in >> material.uniformData
       >> material.objectColor
       >> material.atlasTexId
       >> material.diffuseTexId
       >> material.specularTexId
       >> material.normalTexId
       >> material.heightTexId;

    return in;
}
