#pragma once

#include <QString>

class IEShader;

class IEGlslImporter
{

public:
    static bool importGlsl(const QString& path, IEShader& shader);

private:
    static std::tuple<QString, QString> parseFile(const QString& filePath);
};

