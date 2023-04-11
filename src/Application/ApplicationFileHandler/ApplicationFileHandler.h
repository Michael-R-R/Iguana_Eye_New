#pragma once

#include <QString>

class ApplicationWindow;

class ApplicationFileHandler
{
    ApplicationWindow* application;

    QString savePath;

public:
    ApplicationFileHandler(ApplicationWindow* app);
    ~ApplicationFileHandler();

    void handleFileNew();
    void handleFileOpened(const QString& path);
    void handleFileSaved();
    void handleFileSavedAs(const QString& path);

    const QString& getSavePath() const { return savePath; }
    void setSavePath(const QString val) { savePath = val; }

private:
    bool askToSaveFile();
    QString openSaveFileExplorer();
    void cleanTempFiles();
};

