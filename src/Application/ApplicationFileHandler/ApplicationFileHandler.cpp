#include "ApplicationFileHandler.h"
#include "ApplicationWindow.h"
#include "IEFile.h"
#include "IESerialize.h"
#include <QMessageBox>

ApplicationFileHandler::ApplicationFileHandler(ApplicationWindow* app) :
    application(app),
    savePath("")
{

}

ApplicationFileHandler::~ApplicationFileHandler()
{
    cleanTempFiles();
}

void ApplicationFileHandler::handleFileNew()
{
    if(askToSaveFile())
        this->handleFileSaved();

    savePath = "";
    application->modifyTitle(savePath);
    application->shutdown();
    application->startup();
}

void ApplicationFileHandler::handleFileSaved()
{
    if(savePath.isEmpty())
        return;

    IESerialize::write<ApplicationWindow>(savePath, application);
}

void ApplicationFileHandler::handleFileSavedAs(const QString& path)
{
    if(askToSaveFile())
        this->handleFileSaved();

    if(!IESerialize::write<ApplicationWindow>(path, application))
        return;

    savePath = path;
    application->modifyTitle(savePath);
}

void ApplicationFileHandler::handleFileOpened(const QString& path)
{
    if(askToSaveFile())
        this->handleFileSaved();

    if(!IESerialize::read<ApplicationWindow>(path, application))
        return;

    savePath = path;
    application->modifyTitle(path);
}

bool ApplicationFileHandler::askToSaveFile()
{
    if(savePath.isEmpty())
        return false;

    int answer = QMessageBox::question(application,
                                       "Save File?",
                                       "Save before closing?",
                                       QMessageBox::No | QMessageBox::Yes);

    return (answer == QMessageBox::Yes);
}

void ApplicationFileHandler::cleanTempFiles()
{
    IEFile::removeAllFiles("./resources/temp/backup/");
}

