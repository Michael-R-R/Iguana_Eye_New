#include "IEMaterial.h"
#include "IEShader.h"
#include "IETexture2D.h"
#include "IETexture2DManager.h"
#include "IESerialize.h"

IEMaterial::IEMaterial(QObject* parent) :
    IEFileResource(parent),
    nodes()
{

}

IEMaterial::IEMaterial(const QString& path, QObject* parent) :
    IEFileResource(path, parent),
    nodes()
{

}

IEMaterial::~IEMaterial()
{
    cleanup();
}

void IEMaterial::bindColors(const int index, IEShader& shader)
{
    if(index < 0 || index >= nodes.size())
        return;

    QHashIterator<IEColorType, glm::vec4> it(nodes[index]->colors);
    while(it.hasNext())
    {
        it.next();

        shader.setVec4(nodes[index]->colorNames[it.key()], it.value());
    }
}

void IEMaterial::bindTextures(const int index, IEShader& shader, IETexture2DManager& manager)
{
    if(index < 0 || index >= nodes.size())
        return;

    int counter = 0;

    QHashIterator<IETextureType, QVector<uint64_t>> it(nodes[index]->textureIDs);
    while(it.hasNext())
    {
        it.next();

        const QVector<uint64_t>& values = it.value();
        for(int i = 0; i < values.size(); i++)
        {
            const char* texName = nodes[index]->textureNames[it.key()];
            QString name = QString("%1_%2").arg(texName, QString::number(i));
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

int IEMaterial::appendNode(IEMaterialNode* node)
{
    if(!node) { return -1; }

    const int index = nodes.size();

    nodes.append(node);

    return index;
}

void IEMaterial::remove(const int index)
{
    if(index < 0 || index >= nodes.size())
        return;

    auto* temp = nodes[index];
    nodes.removeAt(index);
    delete temp;
}

IEMaterialNode* IEMaterial::getNode(const int index)
{
    if(index < 0 || index >= nodes.size())
        return nullptr;

    return nodes[index];
}

void IEMaterial::cleanup()
{
     foreach(auto* i, nodes)
    {
        delete i;
        i = nullptr;
    }

    nodes.clear();
}

QDataStream& IEMaterial::serialize(QDataStream& out, const IESerializable& obj) const
{
    IEFileResource::serialize(out, obj);

    const auto& material = static_cast<const IEMaterial&>(obj);

    out << (int)material.nodes.size();
    foreach(auto* i, material.nodes)
    {
        out << *i;
    }

    return out;
}

QDataStream& IEMaterial::deserialize(QDataStream& in, IESerializable& obj)
{
    IEFileResource::deserialize(in, obj);

    auto& material = static_cast<IEMaterial&>(obj);
    material.cleanup();

    int nodeCount = 0;
    in >> nodeCount;
    for(int i = 0; i < nodeCount; i++)
    {
        auto* node = new IEMaterialNode();
        in >> *node;

        material.nodes.append(node);
    }

    return in;
}
