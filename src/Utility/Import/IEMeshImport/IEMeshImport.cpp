#include "IEMeshImport.h"
#include "IEMesh.h"
#include "IEMaterial.h"
#include "IEShader.h"
#include "IETexture2D.h"
#include "IEFile.h"
#include "IEHash.h"
#include "ApplicationWindow.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IETexture2DManager.h"
#include <glm/glm.hpp>
#include <QDebug>

bool IEMeshImport::importPath(const QString& path, IEMesh& me)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.toStdString(), aiProcessPreset_TargetRealtime_MaxQuality);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        qDebug() << "ERROR::ASSIMP::" << importer.GetErrorString();
        return false;
    }

    me.updateId(convertMeshPath(path));

    processNode(scene->mRootNode, scene, &me);

    return true;
}

bool IEMeshImport::importPath(const QString& path, IEMesh& me, IEMaterial& ma)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.toStdString(), aiProcessPreset_TargetRealtime_MaxQuality);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        qDebug() << "ERROR::ASSIMP::" << importer.GetErrorString();
        return false;
    }

    me.updateId(convertMeshPath(path));
    ma.updateId(convertMaterialPath(path));

    processNode(scene->mRootNode, scene, &me, &ma);

    return true;
}

QString IEMeshImport::convertMeshPath(const QString& path)
{
    QString newPath = path;
    QString oldExt = IEFile::extractExtension(path);

    return newPath.replace(oldExt, ".iemesh");
}

QString IEMeshImport::convertMaterialPath(const QString& path)
{
    QString newPath = path;
    QString oldExt = IEFile::extractExtension(path);

    return newPath.replace(oldExt, ".iemat");
}

void IEMeshImport::processNode(aiNode* node, const aiScene* scene, IEMesh* me)
{
    for(unsigned i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* assimpMesh = scene->mMeshes[node->mMeshes[i]];

        IEMeshNode* ieNode = new IEMeshNode();

        processMeshNode(assimpMesh, ieNode);

        me->appendNode(ieNode);
    }

    for(unsigned i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, me);
    }
}

void IEMeshImport::processNode(aiNode* node, const aiScene* scene, IEMesh* me, IEMaterial* ma)
{
    for(unsigned i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* assimpMesh = scene->mMeshes[node->mMeshes[i]];

        IEMeshNode* meshNode = new IEMeshNode();
        IEMaterialNode* materialNode = new IEMaterialNode();

        processMeshNode(assimpMesh, meshNode);
        processMaterialNode(assimpMesh, scene, ma->getName(), materialNode);

        me->appendNode(meshNode);
        ma->appendNode(materialNode);
    }

    for(unsigned i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, me, ma);
    }
}

void IEMeshImport::processMeshNode(aiMesh* assimpMesh, IEMeshNode* meNode)
{
    for(unsigned i = 0; i < assimpMesh->mNumVertices; i++)
    {
        // Position coords
        auto tempPos = assimpMesh->mVertices[i];
        meNode->positions.append(glm::vec3(tempPos.x, tempPos.y, tempPos.z));

        // Normal coords
        if(assimpMesh->HasNormals())
        {
            auto tempNorm = assimpMesh->mNormals[i];
            meNode->normals.append(glm::vec3(tempNorm.x, tempNorm.y, tempNorm.z));
        }
        else
        {
            meNode->normals.append(glm::vec3());
        }

        // Tangents and Bitangets
        if(assimpMesh->HasTangentsAndBitangents())
        {
            auto tempTan = assimpMesh->mTangents[i];
            meNode->tangents.append(glm::vec3(tempTan.x, tempTan.y, tempTan.z));

            auto tempBiTan = assimpMesh->mBitangents[i];
            meNode->bitangents.append(glm::vec3(tempBiTan.x, tempBiTan.y, tempBiTan.z));
        }
        else
        {
            meNode->tangents.append(glm::vec3());
            meNode->bitangents.append(glm::vec3());
        }

        // Texture coords
        if(assimpMesh->HasTextureCoords(0))
        {
            auto tempTex = assimpMesh->mTextureCoords[0][i];
            meNode->textures.append(glm::vec2(tempTex.x, tempTex.y));
        }
        else
        {
            meNode->textures.append(glm::vec2());
        }
    }

    // Face indices
    for(unsigned i = 0; i < assimpMesh->mNumFaces; i++)
    {
        auto face = assimpMesh->mFaces[i];

        for(unsigned j = 0; j < face.mNumIndices; j++)
        {
            meNode->indices.append(face.mIndices[j]);
        }
    }
}

void IEMeshImport::processMaterialNode(aiMesh* assimpMesh, const aiScene* scene, const QString& filePath, IEMaterialNode* maNode)
{
    aiMaterial* assimpMat = scene->mMaterials[assimpMesh->mMaterialIndex];

    // Colors
    aiColor4D ambient;
    aiColor4D diffuse;
    aiColor4D specular;
    aiColor4D emissive;
    aiColor4D reflective;
    aiColor4D transparent;

    if(AI_SUCCESS == aiGetMaterialColor(assimpMat, AI_MATKEY_COLOR_AMBIENT, &ambient))
        maNode->colors.insert(IEColorType::Ambient, glm::vec4(ambient.r, ambient.g, ambient.b, ambient.a));
    if(AI_SUCCESS == aiGetMaterialColor(assimpMat, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
        maNode->colors.insert(IEColorType::Diffuse, glm::vec4(diffuse.r, diffuse.g, diffuse.b, diffuse.a));
    if(AI_SUCCESS == aiGetMaterialColor(assimpMat, AI_MATKEY_COLOR_SPECULAR, &specular))
        maNode->colors.insert(IEColorType::Specular, glm::vec4(specular.r, specular.g, specular.b, specular.a));
    if(AI_SUCCESS == aiGetMaterialColor(assimpMat, AI_MATKEY_COLOR_EMISSIVE, &emissive))
        maNode->colors.insert(IEColorType::Emissive, glm::vec4(emissive.r, emissive.g, emissive.b, emissive.a));
    if(AI_SUCCESS == aiGetMaterialColor(assimpMat, AI_MATKEY_COLOR_REFLECTIVE, &reflective))
        maNode->colors.insert(IEColorType::Reflective, glm::vec4(reflective.r, reflective.g, reflective.b, reflective.a));
    if(AI_SUCCESS == aiGetMaterialColor(assimpMat, AI_MATKEY_COLOR_TRANSPARENT, &transparent))
        maNode->colors.insert(IEColorType::Transparent, glm::vec4(transparent.r, transparent.g, transparent.b, transparent.a));

    // Textures
    auto* game = ApplicationWindow::instance().getGame();
    auto* texManager = game->getSystem<IEScene>()->getSystem<IETexture2DManager>();

    QString relPath = IEFile::extractPath(filePath);
    load2DTextures(relPath, assimpMat, aiTextureType::aiTextureType_AMBIENT, IETextureType::Ambient, maNode, texManager);
    load2DTextures(relPath, assimpMat, aiTextureType::aiTextureType_DIFFUSE, IETextureType::Diffuse, maNode, texManager);
    load2DTextures(relPath, assimpMat, aiTextureType::aiTextureType_SPECULAR, IETextureType::Specular, maNode, texManager);
    load2DTextures(relPath, assimpMat, aiTextureType::aiTextureType_NORMALS, IETextureType::Normals, maNode, texManager);
    load2DTextures(relPath, assimpMat, aiTextureType::aiTextureType_HEIGHT, IETextureType::Height, maNode, texManager);
    load2DTextures(relPath, assimpMat, aiTextureType::aiTextureType_EMISSIVE, IETextureType::Emissive, maNode, texManager);
    load2DTextures(relPath, assimpMat, aiTextureType::aiTextureType_SHININESS, IETextureType::Shininess, maNode, texManager);
    load2DTextures(relPath, assimpMat, aiTextureType::aiTextureType_OPACITY, IETextureType::Opacity, maNode, texManager);
    load2DTextures(relPath, assimpMat, aiTextureType::aiTextureType_DISPLACEMENT, IETextureType::Displacement, maNode, texManager);
    load2DTextures(relPath, assimpMat, aiTextureType::aiTextureType_LIGHTMAP, IETextureType::Lightmap, maNode, texManager);
    load2DTextures(relPath, assimpMat, aiTextureType::aiTextureType_UNKNOWN, IETextureType::Unknown, maNode, texManager);
}

void IEMeshImport::load2DTextures(const QString& relPath,
                                  aiMaterial* assimpMat,
                                  aiTextureType assimpTexType,
                                  IETextureType ieTexType,
                                  IEMaterialNode* maNode,
                                  IETexture2DManager* manager)
{
    for(unsigned i = 0; i < assimpMat->GetTextureCount(assimpTexType); i++)
    {
        aiString assimpPath;
        assimpMat->GetTexture(assimpTexType, i, &assimpPath);

        QString imgPath = relPath + assimpPath.C_Str();
        QString texPath = relPath + IEFile::extractName(imgPath) + ".ietex2d";

        uint64_t hashID = IEHash::Compute(texPath);

        if(!manager->doesExist(hashID))
        {
            auto* texture = new IETexture2D(texPath,
                                            imgPath,
                                            QOpenGLTexture::LinearMipMapLinear,
                                            QOpenGLTexture::Linear,
                                            QOpenGLTexture::Repeat,
                                            QOpenGLTexture::Repeat,
                                            manager);
            if(!texture->build())
            {
                delete texture;
                continue;
            }

            if(!manager->add(texture->getID(), texture))
            {
                delete texture;
                continue;
            }
        }

        maNode->textureIDs[ieTexType].append(hashID);
    }
}
