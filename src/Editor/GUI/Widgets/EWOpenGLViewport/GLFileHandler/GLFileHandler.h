#pragma once

#include <QString>

class GLFileHandler
{

public:
    GLFileHandler();
    ~GLFileHandler();

    void handle(const QString& path);

private:
    void handleObjFile(const QString& path);
    void handleGlslFile(const QString& path);
};

