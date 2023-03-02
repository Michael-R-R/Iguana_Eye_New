#include "ESceneStartup.h"
#include "AppStartEvent.h"
#include "IEGame.h"
#include "IEHash.h"
#include "IESerialize.h"
#include "EGridRenderable.h"

void ESceneStartup::startup(const AppStartEvent& event)
{
    addDefaultCamera(event);
    addDefaultMaterial(event);
    addDefaultShader(event);
    buildGridRenderable(event);
}

void ESceneStartup::addDefaultCamera(const AppStartEvent& event)
{
    auto scene = event.getGame()->getIEScene();
    int width = event.getGame()->getViewportWidth();
    int height = event.getGame()->getViewportHeight();
    float aspectRatio = (float)width / (float)height;

    QString path = "./resources/cameras/game/default.iecam";
    unsigned long long id = IEHash::Compute(path);
    auto camera = new IECamera(path, id);
    camera->updateView(QVector3D(0.0f, 10.0f, -20.0f), QVector3D(0.0f, 0.0f, 0.0f));
    QMatrix4x4 projection;
    projection.perspective(camera->getFOV(), aspectRatio, camera->getNear(), camera->getFar());
    camera->setProjection(projection);
    if(!IESerialize::read<IECamera>(path, camera))
        IESerialize::write<IECamera>(path, camera);
    scene->getCameraManager()->add(id, camera);
}

void ESceneStartup::addDefaultMaterial(const AppStartEvent& event)
{
    auto scene = event.getGame()->getIEScene();

    QString path = "./resources/materials/game/default.iemat";
    unsigned long long id = IEHash::Compute(path);
    auto material = new IEMaterial(path, id);
    if(!IESerialize::read<IEMaterial>(path, material))
        IESerialize::write<IEMaterial>(path, material);
    scene->getMaterialManager()->add(id, material);
}

void ESceneStartup::addDefaultShader(const AppStartEvent& event)
{
    auto scene = event.getGame()->getIEScene();

    QString path = "./resources/shaders/game/default.glsl";
    unsigned long long id = IEHash::Compute(path);
    auto shader = new IEShader(path, id);
    IEGlslImporter::importGlsl(path, shader);
    shader->build();
    scene->getShaderManager()->add(id, shader);
}

void ESceneStartup::buildGridRenderable(const AppStartEvent& event)
{
    auto scene = event.getGame()->getIEScene();
    auto meshManager = scene->getMeshManager();
    auto materialManager = scene->getMaterialManager();
    auto shaderManager = scene->getShaderManager();
    auto renderableManager = scene->getRenderableManager();

    unsigned long long id = IEHash::Compute("EGridRenderable");
    auto gridRenderable = new EGridRenderable(id);
    gridRenderable->setup(meshManager, materialManager, shaderManager);
    renderableManager->add(id, gridRenderable);
}
