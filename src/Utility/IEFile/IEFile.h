#pragma once

#include <QFile>
#include <QTextStream>

class IEFile
{

public:
    static bool write(const QString& path, const QString& outData);
    static bool read(const QString& path, QString* inData);
    static QString extractName(const QString& path);
};

