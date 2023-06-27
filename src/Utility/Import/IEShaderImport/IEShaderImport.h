#pragma once

#include <QString>

class IEShader;

class IEShaderImport
{

public:
    static bool importGlsl(const QString& path, IEShader& shader);
    static bool importGlsl(const QString& path, QString& vSrc, QString& fSrc);

private:
    static std::tuple<QString, QString> parseFile(const QString& filePath);
};

