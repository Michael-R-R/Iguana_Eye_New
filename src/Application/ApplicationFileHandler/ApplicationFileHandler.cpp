#include "ApplicationFileHandler.h"
#include "ApplicationWindow.h"
#include "IEFile.h"
#include "IESerialize.h"
#include <QMessageBox>
#include <QFileDialog>

ApplicationFileHandler::ApplicationFileHandler(ApplicationWindow* app) :
    application(app),
    savePath("")
{

}

ApplicationFileHandler::~ApplicationFileHandler()
{
    cleanTempFiles();
}

void ApplicationFileHandler::handleNewFile()
{
    if(askToSaveFile())
        this->handleSaveFile();

    savePath = "";
    application->modifyTitle(savePath);
    application->shutdown();
    application->startup();
}

void ApplicationFileHandler::handleSaveFile()
{
    if(savePath.isEmpty())
    {
        savePath = openSaveFileExplorer();
        if(savePath.isEmpty())
            return;

        application->modifyTitle(savePath);
    }

    IESerialize::write<ApplicationWindow>(savePath, application);
}

void ApplicationFileHandler::handleSaveAsFile(const QString& path)
{
    if(askToSaveFile())
        this->handleSaveFile();

    if(!IESerialize::write<ApplicationWindow>(path, application))
        return;

    savePath = path;
    application->modifyTitle(savePath);
}

void ApplicationFileHandler::handleOpenFile(const QString& path)
{
    if(askToSaveFile())
        this->handleSaveFile();

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

QString ApplicationFileHandler::openSaveFileExplorer()
{
    QString path = QFileDialog::getSaveFileName(application,
                                                "Save File...",
                                                ".",
                                                "Iguana Eye File (*.iedat)");
    return path;
}

void ApplicationFileHandler::cleanTempFiles()
{
    IEFile::removeAllFiles("./resources/temp/backup/");
}

