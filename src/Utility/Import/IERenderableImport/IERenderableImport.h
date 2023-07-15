#pragma once

#include <QString>

class QObject;
class IEMesh;
class IERenderable;
struct IEMeshNode;
struct IERenderableNode;

class IERenderableImport
{
public:
    static bool importPath(const QString& path,
                           IERenderable& renderable,
                           IEMesh& mesh,
                           const uint64_t maID,
                           const uint64_t sID);
    static QString convertRenderablePath(const QString& path);

private:
    static void processRenderableNode(IEMeshNode* meNode, IERenderableNode* rNode, QObject* parent);
};

