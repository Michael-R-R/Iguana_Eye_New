#pragma once

#include <QString>

class IEShaderExport
{
public:
    static bool exportShader(const QString& path, const QString& vSrc, const QString& fSrc);
};

