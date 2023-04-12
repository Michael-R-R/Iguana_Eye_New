#pragma once

#include <QString>

class EWGlslEditor;

class GlslFileHandler
{
    // DOES NOT OWN THIS POINTER
    EWGlslEditor* glslEditor;

public:
    GlslFileHandler(EWGlslEditor* editor);
    ~GlslFileHandler();

    void handleGlslNew(const QString& path);
    void handleGlslOpen(const QString& path);
    void handleGlslSave(const QString& path);
    void handleGlslSaveAs(const QString& path);

private:
    bool askToSaveFile();
    QString openSaveFileExplorer();
};

