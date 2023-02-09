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
