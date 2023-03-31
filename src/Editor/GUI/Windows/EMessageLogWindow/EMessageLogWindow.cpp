#include "EMessageLogWindow.h"
#include "AppStartEvent.h"
#include "IEGame.h"
#include "IETime.h"
#include "IEScriptEngine.h"
#include "IEPhysicsEngine.h"
#include "IERenderEngine.h"
#include "IEScene.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"
#include "IECameraManager.h"
#include "IEECS.h"

EMessageLogWindow::EMessageLogWindow(QWidget* parent) :
    EWindow("Message Log", parent),
    messageLog(new EWMessageLog(this))
{
    this->setWidget(messageLog);
}

EMessageLogWindow::~EMessageLogWindow()
{

}

void EMessageLogWindow::startup(const AppStartEvent& event)
{
    auto* game = event.getGame();
    auto& scene = game->getIEScene();

    connect(&game->getIETime(), &IETime::message, messageLog, &EWMessageLog::insertMessage);
    connect(&game->getIEScriptEngine(), &IEScriptEngine::message, messageLog, &EWMessageLog::insertMessage);
    connect(&game->getIEPhysicsEngine(), &IEPhysicsEngine::message, messageLog, &EWMessageLog::insertMessage);
    connect(&game->getIERenderEngine(), &IERenderEngine::message, messageLog, &EWMessageLog::insertMessage);
    connect(&game->getECS(), &IEECS::message, messageLog, &EWMessageLog::insertMessage);
    connect(&scene, &IEScene::message, messageLog, &EWMessageLog::insertMessage);
    connect(&scene.getMeshManager(), &IEMeshManager::message, messageLog, &EWMessageLog::insertMessage);
    connect(&scene.getMaterialManager(), &IEMaterialManager::message, messageLog, &EWMessageLog::insertMessage);
    connect(&scene.getShaderManager(), &IEShaderManager::message, messageLog, &EWMessageLog::insertMessage);
    connect(&scene.getRenderableManager(), &IERenderableManager::message, messageLog, &EWMessageLog::insertMessage);
    connect(&scene.getCameraManager(), &IECameraManager::message, messageLog, &EWMessageLog::insertMessage);
}
