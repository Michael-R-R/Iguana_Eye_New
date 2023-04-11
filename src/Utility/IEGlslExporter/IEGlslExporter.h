#pragma once

#include <QString>

class IEGlslExporter
{
public:
    static bool exportGlsl(const QString& path, const QString& vSrc, const QString& fSrc);
};

