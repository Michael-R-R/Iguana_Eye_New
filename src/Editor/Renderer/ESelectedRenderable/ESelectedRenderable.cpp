#include "ESelectedRenderable.h"
#include "EPhysicsEngine.h"
#include "IEShader.h"
#include "IEEntity.h"
#include "IEFile.h"
#include "IEGlslImporter.h"
#include "IECamera.h"
#include "IEMesh.h"
#include "IERenderable.h"
#include "IEECSTransformSystem.h"
#include "IEECSMeshSystem.h"
#include "IEECSRenderableSystem.h"
#include "ApplicationWindow.h"
#include "IEGame.h"
#include "IEECS.h"
#include <QMatrix4x4>
#include <QOpenGLExtraFunctions>

ESelectedRenderable::ESelectedRenderable(EPhysicsEngine* physicsEngine, QObject* parent) :
    IEObject(parent),
    shader(new IEShader(IEFile::absolutePath("./resources/shaders/editor/obj_outline.glsl"), this)),
    entities()
{
    IEGlslImporter::importGlsl("./resources/shaders/editor/obj_outline.glsl", *shader);
    shader->build();

    connect(physicsEngine, &EPhysicsEngine::entitySelected, this, &ESelectedRenderable::addEntity);
    connect(physicsEngine, &EPhysicsEngine::selectionCleared, this, &ESelectedRenderable::clearSelection);
}

ESelectedRenderable::~ESelectedRenderable()
{

}

void ESelectedRenderable::predraw(QOpenGLExtraFunctions* glFunc)
{
    glFunc->glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glFunc->glStencilFunc(GL_ALWAYS, 1, 0xff);
    glFunc->glStencilMask(0xFF);
}

void ESelectedRenderable::draw(QOpenGLExtraFunctions* glFunc, IECamera* camera)
{
    glFunc->glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glFunc->glStencilMask(0x00);
    glFunc->glDisable(GL_DEPTH_TEST);

    auto* game = ApplicationWindow::instance().getGame();
    auto* ecs = game->getECS();
    auto* tSystem = ecs->getComponent<IEECSTransformSystem>();
    auto* mSystem = ecs->getComponent<IEECSMeshSystem>();
    auto* rSystem = ecs->getComponent<IEECSRenderableSystem>();

    for(auto& i : entities)
    {
        shader->bind();

        int tIndex = tSystem->lookUpIndex(i);
        const auto& pos = tSystem->getPosition(tIndex);
        const auto& rot = tSystem->getRotation(tIndex);
        const auto& scl = tSystem->getScale(tIndex);

        QMatrix4x4 transform;
        transform.translate(pos);
        transform.rotate(rot.w(), rot.x(), rot.y(), rot.z());
        float val = 1.05f;
        transform.scale(scl.x() * val, scl.y() * val, scl.z() * val);

        int mIndex = mSystem->lookUpIndex(i);
        auto mesh = mSystem->getAttachedMesh(mIndex);

        int rIndex = rSystem->lookUpIndex(i);
        auto renderable = rSystem->getAttachedRenderable(rIndex);

        shader->setUniformValue("uVPM", camera->getViewProjection() * transform);
        renderable->bind();

        glFunc->glDrawElements(GL_TRIANGLES, mesh->getIndices().size(), GL_UNSIGNED_INT, 0);

        shader->release();
        renderable->release();
    }

    glFunc->glStencilMask(0xFF);
    glFunc->glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glFunc->glEnable(GL_DEPTH_TEST);
}

void ESelectedRenderable::addEntity(const IEEntity& entity)
{
    entities[entity.getId()] = entity;
}

void ESelectedRenderable::clearSelection()
{
    entities.clear();
}

