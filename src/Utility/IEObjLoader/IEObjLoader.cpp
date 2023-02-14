#include "IEObjLoader.h"
#include "IEMesh.h"
#include <QDebug>
#include <QVector3D>
#include <QVector2D>

IEMesh* IEObjLoader::loadMesh(const QString& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.toStdString(), aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        qDebug() << "ERROR::ASSIMP::" << importer.GetErrorString();
        return nullptr;
    }

    return processNode(scene->mRootNode, scene, new IEMesh());
}

IEMesh* IEObjLoader::processNode(aiNode* node, const aiScene* scene, IEMesh* ieMesh)
{
    for(unsigned i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* assimpMesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(assimpMesh, scene, ieMesh);
    }

    for(unsigned i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, ieMesh);
    }

    return ieMesh;
}

IEMesh* IEObjLoader::processMesh(aiMesh* assimpMesh, const aiScene* scene, IEMesh* ieMesh)
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

    return ieMesh;
}
