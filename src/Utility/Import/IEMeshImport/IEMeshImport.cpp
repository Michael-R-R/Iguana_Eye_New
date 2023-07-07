#include "IEMeshImport.h"
#include "IEMesh.h"
#include "IEMaterial.h"
#include "IEShader.h"
#include "IERenderable.h"
#include "IETexture2D.h"
#include "IERenderableFactory.h"
#include "IEBufferObjectFactory.h"
#include "IEFile.h"
#include "IEHash.h"
#include "ApplicationWindow.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IETexture2DManager.h"
#include <QVector2D>
#include <QVector3D>
#include <QDebug>

bool IEMeshImport::importMesh(const QString& path, IEMesh& mesh)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.toStdString(), aiProcessPreset_TargetRealtime_MaxQuality);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        qDebug() << "ERROR::ASSIMP::" << importer.GetErrorString();
        return false;
    }

    replaceExtension(path, ".iemesh", mesh);

    processNode(scene->mRootNode, scene, &mesh);

    return true;
}

bool IEMeshImport::importMesh(const QString& path, IEMesh& mesh, IEMaterial& material)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.toStdString(), aiProcessPreset_TargetRealtime_MaxQuality);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        qDebug() << "ERROR::ASSIMP::" << importer.GetErrorString();
        return false;
    }

    replaceExtension(path, ".iemesh", mesh);
    replaceExtension(path, ".iemat", material);

    processNode(scene->mRootNode, scene, &mesh, &material);

    return true;
}

bool IEMeshImport::importMesh(const QString& path, IEMesh& mesh, IEMaterial& material, IEShader& shader, IERenderable& renderable)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.toStdString(), aiProcessPreset_TargetRealtime_MaxQuality);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        qDebug() << "ERROR::ASSIMP::" << importer.GetErrorString();
        return false;
    }

    replaceExtension(path, ".iemesh", mesh);
    replaceExtension(path, ".iemat", material);
    replaceExtension(path, ".ierend", renderable);

    renderable.setMeshId(mesh.getId());
    renderable.setMaterialId(material.getId());
    renderable.setShaderId(shader.getId());

    processNode(scene->mRootNode, scene, &mesh, &material, &renderable);

    return true;
}

void IEMeshImport::replaceExtension(QString path, const QString extension, IEResource& resource)
{
    QString ext = IEFile::extractExtension(path);
    path = path.replace(ext, extension);

    resource.updateId(path);
}

void IEMeshImport::processNode(aiNode* node, const aiScene* scene, IEMesh* meParent)
{
    for(unsigned i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* assimpMesh = scene->mMeshes[node->mMeshes[i]];

        auto* mesh = new IEMesh(meParent->getName(), meParent);
        mesh->setParent(meParent);
        processMesh(assimpMesh, mesh);
        meParent->getMeshes().append(mesh);
    }

    for(unsigned i = 0; i < node->mNumChildren; i++)
    {
        auto* childMesh = new IEMesh(meParent->getName(), meParent);
        childMesh->setParent(meParent);
        processNode(node->mChildren[i], scene, childMesh);
        meParent->getChildren().append(childMesh);
    }
}

void IEMeshImport::processNode(aiNode* node, const aiScene* scene, IEMesh* meParent, IEMaterial* maParent)
{
    for(unsigned i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* assimpMesh = scene->mMeshes[node->mMeshes[i]];

        auto* mesh = new IEMesh(meParent->getName(), meParent);
        mesh->setParent(meParent);

        auto* material = new IEMaterial(maParent->getName(), maParent);
        material->setParent(maParent);

        processMesh(assimpMesh, mesh);
        processMaterial(assimpMesh, scene, material);

        meParent->getMeshes().append(mesh);
        maParent->getMaterials().append(material);
    }

    for(unsigned i = 0; i < node->mNumChildren; i++)
    {
        auto* childMesh = new IEMesh(meParent->getName(), meParent);
        childMesh->setParent(meParent);

        auto* childMaterial = new IEMaterial(maParent->getName(), maParent);
        childMaterial->setParent(maParent);

        processNode(node->mChildren[i], scene, childMesh, childMaterial);

        meParent->getChildren().append(childMesh);
        maParent->getChildren().append(childMaterial);
    }
}

void IEMeshImport::processNode(aiNode* node, const aiScene* scene, IEMesh* meParent, IEMaterial* maParent, IERenderable* rParent)
{
    for(unsigned i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* assimpMesh = scene->mMeshes[node->mMeshes[i]];

        auto* mesh = new IEMesh(meParent->getName(), meParent);
        mesh->setParent(meParent);

        auto* material = new IEMaterial(maParent->getName(), maParent);
        material->setParent(maParent);

        auto* renderable = IERenderableFactory::make(rParent->getType(), rParent);
        renderable->setParent(rParent);
        renderable->setMeshId(rParent->getMeshId());
        renderable->setMaterialId(rParent->getMaterialId());
        renderable->setShaderId(rParent->getShaderId());

        processMesh(assimpMesh, mesh);
        processMaterial(assimpMesh, scene, material);
        processRenderable(mesh, renderable);

        meParent->getMeshes().append(mesh);
        maParent->getMaterials().append(material);
        rParent->getRenderables().append(renderable);
    }

    for(unsigned i = 0; i < node->mNumChildren; i++)
    {
        auto* childMesh = new IEMesh(meParent->getName(), meParent);
        childMesh->setParent(meParent);

        auto* childMaterial = new IEMaterial(maParent->getName(), maParent);
        childMaterial->setParent(maParent);

        auto* childRenderable = IERenderableFactory::make(rParent->getType(), rParent);
        childRenderable->setParent(rParent);

        processNode(node->mChildren[i], scene, childMesh, childMaterial, childRenderable);

        meParent->getChildren().append(childMesh);
        maParent->getChildren().append(childMaterial);
        rParent->getChildren().append(childRenderable);
    }
}

void IEMeshImport::processMesh(aiMesh* assimpMesh, IEMesh* ieMesh)
{
    auto& posVerts = ieMesh->getPosVertices();
    auto& normVerts = ieMesh->getNormVertices();
    auto& tanVerts = ieMesh->getTanVertices();
    auto& bitanVerts = ieMesh->getBiTanVertices();
    auto& texVerts = ieMesh->getTexVertices();
    auto& indices = ieMesh->getIndices();

    for(unsigned i = 0; i < assimpMesh->mNumVertices; i++)
    {
        // Position coords
        auto tempPos = assimpMesh->mVertices[i];
        posVerts.append(QVector3D(tempPos.x, tempPos.y, tempPos.z));

        // Normal coords
        if(assimpMesh->HasNormals())
        {
            auto tempNorm = assimpMesh->mNormals[i];
            normVerts.append(QVector3D(tempNorm.x, tempNorm.y, tempNorm.z));
        }
        else
        {
            normVerts.append(QVector3D());
        }

        // Tangents and Bitangets
        if(assimpMesh->HasTangentsAndBitangents())
        {
            auto tempTan = assimpMesh->mTangents[i];
            tanVerts.append(QVector3D(tempTan.x, tempTan.y, tempTan.z));

            auto tempBiTan = assimpMesh->mBitangents[i];
            bitanVerts.append(QVector3D(tempBiTan.x, tempBiTan.y, tempBiTan.z));
        }
        else
        {
            tanVerts.append(QVector3D());
            bitanVerts.append(QVector3D());
        }

        // Texture coords
        if(assimpMesh->HasTextureCoords(0))
        {
            auto tempTex = assimpMesh->mTextureCoords[0][i];
            texVerts.append(QVector2D(tempTex.x, tempTex.y));
        }
        else
        {
            texVerts.append(QVector2D());
        }
    }

    // Face indices
    for(unsigned i = 0; i < assimpMesh->mNumFaces; i++)
    {
        auto face = assimpMesh->mFaces[i];

        for(unsigned j = 0; j < face.mNumIndices; j++)
        {
            indices.append(face.mIndices[j]);
        }
    }
}

void IEMeshImport::processMaterial(aiMesh* assimpMesh, const aiScene* scene, IEMaterial* ieMaterial)
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
        ieMaterial->setColor(IEColorType::Ambient, QVector4D(ambient.r, ambient.g, ambient.b, ambient.a));
    if(AI_SUCCESS == aiGetMaterialColor(assimpMat, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
        ieMaterial->setColor(IEColorType::Diffuse, QVector4D(diffuse.r, diffuse.g, diffuse.b, diffuse.a));
    if(AI_SUCCESS == aiGetMaterialColor(assimpMat, AI_MATKEY_COLOR_SPECULAR, &specular))
        ieMaterial->setColor(IEColorType::Specular, QVector4D(specular.r, specular.g, specular.b, specular.a));
    if(AI_SUCCESS == aiGetMaterialColor(assimpMat, AI_MATKEY_COLOR_EMISSIVE, &emissive))
        ieMaterial->setColor(IEColorType::Emissive, QVector4D(emissive.r, emissive.g, emissive.b, emissive.a));
    if(AI_SUCCESS == aiGetMaterialColor(assimpMat, AI_MATKEY_COLOR_REFLECTIVE, &reflective))
        ieMaterial->setColor(IEColorType::Reflective, QVector4D(reflective.r, reflective.g, reflective.b, reflective.a));
    if(AI_SUCCESS == aiGetMaterialColor(assimpMat, AI_MATKEY_COLOR_TRANSPARENT, &transparent))
        ieMaterial->setColor(IEColorType::Transparent, QVector4D(transparent.r, transparent.g, transparent.b, transparent.a));

    // Textures
    auto* game = ApplicationWindow::instance().getGame();
    auto* texManager = game->getSystem<IEScene>()->getManager<IETexture2DManager>();

    QString relPath = IEFile::extractPath(ieMaterial->getName());
    load2DTextures(relPath, assimpMat, aiTextureType::aiTextureType_AMBIENT, IETextureType::Ambient, ieMaterial, texManager);
    load2DTextures(relPath, assimpMat, aiTextureType::aiTextureType_DIFFUSE, IETextureType::Diffuse, ieMaterial, texManager);
    load2DTextures(relPath, assimpMat, aiTextureType::aiTextureType_SPECULAR, IETextureType::Specular, ieMaterial, texManager);
    load2DTextures(relPath, assimpMat, aiTextureType::aiTextureType_NORMALS, IETextureType::Normals, ieMaterial, texManager);
    load2DTextures(relPath, assimpMat, aiTextureType::aiTextureType_HEIGHT, IETextureType::Height, ieMaterial, texManager);
    load2DTextures(relPath, assimpMat, aiTextureType::aiTextureType_EMISSIVE, IETextureType::Emissive, ieMaterial, texManager);
    load2DTextures(relPath, assimpMat, aiTextureType::aiTextureType_SHININESS, IETextureType::Shininess, ieMaterial, texManager);
    load2DTextures(relPath, assimpMat, aiTextureType::aiTextureType_OPACITY, IETextureType::Opacity, ieMaterial, texManager);
    load2DTextures(relPath, assimpMat, aiTextureType::aiTextureType_DISPLACEMENT, IETextureType::Displacement, ieMaterial, texManager);
    load2DTextures(relPath, assimpMat, aiTextureType::aiTextureType_LIGHTMAP, IETextureType::Lightmap, ieMaterial, texManager);
    load2DTextures(relPath, assimpMat, aiTextureType::aiTextureType_UNKNOWN, IETextureType::Unknown, ieMaterial, texManager);
}

void IEMeshImport::processRenderable(IEMesh* mesh, IERenderable* renderable)
{
    renderable->addBuffer("aPos", IEBufferObjectFactory::make(IEBufferType::Vec3, 0, 0, 0, renderable));
    renderable->addBuffer("aNormal", IEBufferObjectFactory::make(IEBufferType::Vec3, 0, 0, 0, renderable));
    renderable->addBuffer("aTangent", IEBufferObjectFactory::make(IEBufferType::Vec3, 0, 0, 0, renderable));
    renderable->addBuffer("aBitangent", IEBufferObjectFactory::make(IEBufferType::Vec3, 0, 0, 0, renderable));
    renderable->addBuffer("aTexCoord", IEBufferObjectFactory::make(IEBufferType::Vec2, 0, 0, 0, renderable));

    renderable->setBufferValues("aPos", mesh->getPosVertices());
    renderable->setBufferValues("aNormal", mesh->getNormVertices());
    renderable->setBufferValues("aTangent", mesh->getTanVertices());
    renderable->setBufferValues("aBitangent", mesh->getBiTanVertices());
    renderable->setBufferValues("aTexCoord", mesh->getTexVertices());
}

void IEMeshImport::load2DTextures(const QString& relPath,
                                  aiMaterial* assimpMat,
                                  aiTextureType assimpTexType,
                                  IETextureType ieTexType,
                                  IEMaterial* ieMaterial,
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

            if(!manager->add(texture->getId(), texture))
            {
                delete texture;
                continue;
            }
        }

        ieMaterial->appendTextureID(ieTexType, hashID);
    }
}






