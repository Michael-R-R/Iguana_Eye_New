#include "IEMeshImport.h"
#include "IEMesh.h"
#include "IEMaterial.h"
#include "IEFile.h"
#include <QVector2D>
#include <QVector3D>
#include <QDebug>

bool IEMeshImport::importMesh(const QString& path, IEMesh& ieMesh)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.toStdString(), aiProcessPreset_TargetRealtime_MaxQuality);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        qDebug() << "ERROR::ASSIMP::" << importer.GetErrorString();
        return false;
    }

    processNode(scene->mRootNode, scene, &ieMesh);

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

    QString tempPath = path;
    QString extension = IEFile::extractExtension(tempPath);
    QString matPath = tempPath.replace(extension, ".iemat");
    material.updateId(matPath);

    processNode(scene->mRootNode, scene, &mesh, &material);
}

void IEMeshImport::processNode(aiNode* node, const aiScene* scene, IEMesh* ieMesh)
{
    for(unsigned i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* assimpMesh = scene->mMeshes[node->mMeshes[i]];

        auto* mesh = new IEMesh(ieMesh->getName(), ieMesh);
        mesh->setParent(ieMesh);
        processMesh(assimpMesh, mesh);
        ieMesh->getMeshes().append(mesh);
    }

    for(unsigned i = 0; i < node->mNumChildren; i++)
    {
        auto* childMesh = new IEMesh(ieMesh->getName(), ieMesh);
        childMesh->setParent(ieMesh);
        processNode(node->mChildren[i], scene, childMesh);
        ieMesh->getChildren().append(childMesh);
    }
}

void IEMeshImport::processNode(aiNode* node, const aiScene* scene, IEMesh* ieMesh, IEMaterial* ieMaterial)
{
    for(unsigned i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* assimpMesh = scene->mMeshes[node->mMeshes[i]];

        auto* mesh = new IEMesh(ieMesh->getName(), ieMesh);
        mesh->setParent(ieMesh);

        auto* material = new IEMaterial(ieMaterial->getName(), ieMaterial);
        material->setParent(ieMaterial);

        processMesh(assimpMesh, mesh);
        processMaterial(assimpMesh, scene, material);

        ieMesh->getMeshes().append(mesh);
        ieMaterial->getMaterials().append(material);
    }

    for(unsigned i = 0; i < node->mNumChildren; i++)
    {
        auto* childMesh = new IEMesh(ieMesh->getName(), ieMesh);
        childMesh->setParent(ieMesh);

        auto* childMaterial = new IEMaterial(ieMaterial->getName(), ieMaterial);
        childMaterial->setParent(ieMaterial);

        processNode(node->mChildren[i], scene, childMesh, childMaterial);

        ieMesh->getChildren().append(childMesh);
        ieMaterial->getChildren().append(childMaterial);
    }
}

void IEMeshImport::processMesh(aiMesh* assimpMesh, IEMesh* ieMesh)
{
    for(unsigned i = 0; i < assimpMesh->mNumVertices; i++)
    {
        // Position coords
        auto tempPos = assimpMesh->mVertices[i];
        ieMesh->getPosVertices().append(QVector3D(tempPos.x, tempPos.y, tempPos.z));

        // Normal coords
        if(assimpMesh->HasNormals())
        {
            auto tempNorm = assimpMesh->mNormals[i];
            ieMesh->getNormVertices().append(QVector3D(tempNorm.x, tempNorm.y, tempNorm.z));
        }
        else
        {
            ieMesh->getNormVertices().append(QVector3D());
        }

        // Tangents and Bitangets
        if(assimpMesh->HasTangentsAndBitangents())
        {
            auto tempTan = assimpMesh->mTangents[i];
            ieMesh->getTanVertices().append(QVector3D(tempTan.x, tempTan.y, tempTan.z));

            auto tempBiTan = assimpMesh->mBitangents[i];
            ieMesh->getBiTanVertices().append(QVector3D(tempBiTan.x, tempBiTan.y, tempBiTan.z));
        }
        else
        {
            ieMesh->getTanVertices().append(QVector3D());
            ieMesh->getBiTanVertices().append(QVector3D());
        }

        // Texture coords
        if(assimpMesh->HasTextureCoords(0))
        {
            auto tempTex = assimpMesh->mTextureCoords[0][i];
            ieMesh->getTexVertices().append(QVector2D(tempTex.x, tempTex.y));
        }
        else
        {
            ieMesh->getTexVertices().append(QVector2D());
        }
    }

    // Face indices
    for(unsigned i = 0; i < assimpMesh->mNumFaces; i++)
    {
        auto face = assimpMesh->mFaces[i];

        for(unsigned j = 0; j < face.mNumIndices; j++)
        {
            ieMesh->getIndices().append(face.mIndices[j]);
        }
    }
}

void IEMeshImport::processMaterial(aiMesh* assimpMesh, const aiScene* scene, IEMaterial* ieMaterial)
{
    aiMaterial* material = scene->mMaterials[assimpMesh->mMaterialIndex];

    aiColor4D ambient;
    aiColor4D diffuse;
    aiColor4D specular;
    aiColor4D emissive;
    aiColor4D reflective;
    aiColor4D transparent;

    if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambient))
        ieMaterial->setColor(IEColorType::Ambient, QVector4D(ambient.r, ambient.g, ambient.b, ambient.a));
    if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
        ieMaterial->setColor(IEColorType::Diffuse, QVector4D(diffuse.r, diffuse.g, diffuse.b, diffuse.a));
    if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specular))
        ieMaterial->setColor(IEColorType::Specular, QVector4D(specular.r, specular.g, specular.b, specular.a));
    if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_EMISSIVE, &emissive))
        ieMaterial->setColor(IEColorType::Emissive, QVector4D(emissive.r, emissive.g, emissive.b, emissive.a));
    if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_REFLECTIVE, &reflective))
        ieMaterial->setColor(IEColorType::Reflective, QVector4D(reflective.r, reflective.g, reflective.b, reflective.a));
    if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_TRANSPARENT, &transparent))
        ieMaterial->setColor(IEColorType::Transparent, QVector4D(transparent.r, transparent.g, transparent.b, transparent.a));

    // TODO load textures once we have texture manager
}
