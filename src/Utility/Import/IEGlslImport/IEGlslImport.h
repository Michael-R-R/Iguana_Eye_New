#pragma once

#include <QString>

class IEShader;

class IEGlslImport
{

public:
    static bool importPath(const QString& path, IEShader& shader);
    static bool importPath(const QString& path, QString& vSrc, QString& fSrc);
    static QString convertPath(const QString& path);

private:
    static std::tuple<QString, QString> parseFile(const QString& filePath);
    static void processIncludes(QString& src);
};

