#pragma once

#include <QString>

class OpenGLFileHandler
{

public:
    OpenGLFileHandler();
    ~OpenGLFileHandler();

    void handle(const QString& path);

private:
    void handleObjFile(const QString& path);
    void handleGlslFile(const QString& path);
};

