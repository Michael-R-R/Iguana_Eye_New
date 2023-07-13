#pragma once

#include <QHash>
#include <QVector>
#include <glm/glm.hpp>

#include "IEFileResource.h"
#include "IEEnum.h"

class IEShader;
class IETexture2DManager;

struct IEMaterialNode
{
    QHash<IEColorType, glm::vec4> colors;
    QHash<IETextureType, QVector<uint64_t>> textureIDs;

    QHash<IEColorType, const char*> colorNames;
    QHash<IETextureType, const char*> textureNames;

    IEMaterialNode() :
        colors(), textureIDs(),
        colorNames(), textureNames()
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
};

class IEMaterial : public IEFileResource
{
protected:
    QVector<IEMaterialNode*> nodes;

public:
    IEMaterial(QObject* parent = nullptr);
    IEMaterial(const QString& path, QObject* parent = nullptr);
    IEMaterial(const IEMaterial&) = delete;
    virtual ~IEMaterial();

    bool operator==(const IEMaterial& other) { return IEFileResource::operator==(other); }
    bool operator!=(const IEMaterial& other) { return IEFileResource::operator!=(other); }
    bool operator<(const IEMaterial& other) { return IEFileResource::operator<(other); }
    bool operator>(const IEMaterial& other) { return IEFileResource::operator>(other); }

    void bindColors(const int index, IEShader& shader);
    void bindTextures(const int index, IEShader& shader, IETexture2DManager& manager);

    int appendNode(IEMaterialNode* node);
    void remove(const int index);
    IEMaterialNode* getNode(const int index);
    void cleanup();

    QVector<IEMaterialNode*>& getNodes() { return nodes; }

    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;
};
