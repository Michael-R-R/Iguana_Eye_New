#pragma once

#include <QString>

class IEFile
{

public:
    static bool write(const QString& path, const QString& outData);
    static bool read(const QString& path, QString* inData);
    static bool removeAllFiles(const QString& path);
    static bool makePath(const QString& path);
    static bool removePath(const QString& path);
    static bool doesPathExist(const QString& path);
    static QString absolutePath(const QString& path);
    static QString extractName(const QString& path);
    static QString extractExtension(const QString& path);

private:
    static QString removeFileName(const QString& path);
};

