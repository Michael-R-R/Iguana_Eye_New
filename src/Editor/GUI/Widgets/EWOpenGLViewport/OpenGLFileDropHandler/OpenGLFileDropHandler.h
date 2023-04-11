#pragma once

#include <QString>

class QOpenGLWidget;

class OpenGLFileDropHandler
{

public:
    OpenGLFileDropHandler();
    ~OpenGLFileDropHandler();

    void handle(QOpenGLWidget* glWidget, const QString& path);

private:
    void handleObjFile(QOpenGLWidget* glWidget, const QString& path);
    void handleGlslFile(const QString& path);
};

