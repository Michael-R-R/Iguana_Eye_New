#include "IEMaterial.h"
#include "IEShader.h"

IEMaterial::IEMaterial() :
    IEResource(0),
    uniformData(), objectColor(),
    atlasTexId(0), diffuseTexId(0),
    specularTexId(0), normalTexId(0),
    heightTexId(0)
{

}

IEMaterial::IEMaterial(const unsigned long long id) :
    IEResource(id),
    uniformData(), objectColor(),
    atlasTexId(0), diffuseTexId(0),
    specularTexId(0), normalTexId(0),
    heightTexId(0)
{

}

IEMaterial::IEMaterial(const IEMaterial& other) :
    IEResource(0),
    uniformData(other.uniformData), objectColor(other.objectColor),
    atlasTexId(other.atlasTexId), diffuseTexId(other.diffuseTexId),
    specularTexId(other.specularTexId), normalTexId(other.normalTexId),
    heightTexId(other.heightTexId)
{

}

IEMaterial::~IEMaterial()
{

}

void IEMaterial::bindUniformData(IEShader* shader) const
{
    uniformData.bind(shader);
}

QDataStream& operator<<(QDataStream& out, const IEMaterial& material)
{
    out << material.getId() << material.getUniformData()
        << material.getObjectColor() << material.getAtlasTexId()
        << material.getDiffuseTexId() << material.getSpecularTexId()
        << material.getNormalTexId() << material.getHeightTexId();

    return out;
}

QDataStream& operator>>(QDataStream& in, IEMaterial& material)
{
    unsigned long long id = 0;
    IEUniform uniformData;
    QColor objectColor;
    unsigned long long atlasTexId = 0;
    unsigned long long diffuseTexId = 0;
    unsigned long long specularTexId = 0;
    unsigned long long normalTexId = 0;
    unsigned long long heightTexId = 0;

    in >> id >> uniformData
       >> objectColor >> atlasTexId
       >> diffuseTexId >> specularTexId
       >> normalTexId >> heightTexId;

    material.setId(id);
    material.setUniformData(uniformData);
    material.setObjectColor(objectColor);
    material.setAtlasTexId(atlasTexId);
    material.setDiffuseTexId(diffuseTexId);
    material.setSpecularTexId(specularTexId);
    material.setNormalTexId(normalTexId);
    material.setHeightTexId(heightTexId);

    return in;
}
