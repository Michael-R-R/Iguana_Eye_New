#include "IEFile.h"
#include <QFile>
#include <QDir>
#include <QTextStream>

bool IEFile::write(const QString& path, const QString& outData)
{
    QFile outFile(path);
    if(!outFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream outStream(&outFile);
    outStream << outData;

    outFile.close();

    return true;
}

bool IEFile::read(const QString& path, QString* inData)
{
    if(!inData)
        return false;

    QFile inFile(path);
    if(!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream inStream(&inFile);
    inData->append(inStream.readAll());

    inFile.close();

    return true;
}

bool IEFile::removeFile(const QString& path)
{
    if(path.isEmpty())
        return false;

    QFile file(path);
    return file.remove();
}

bool IEFile::removeAllFiles(const QString& path)
{
    if(path.isEmpty())
        return false;

    QDir removeDirFiles(path);
    removeDirFiles.setNameFilters(QStringList() << "*.*");
    removeDirFiles.setFilter(QDir::Files);
    foreach(QString file, removeDirFiles.entryList())
    {
        removeDirFiles.remove(file);
    }

    return true;
}

bool IEFile::makePath(const QString& path)
{
    QString tempPath = removeFileName(path);

    QDir dir("");
    return dir.mkpath(tempPath);
}

bool IEFile::removePath(const QString& path)
{
    QString tempPath = removeFileName(path);
    removeAllFiles(tempPath);

    QDir dir("");
    return dir.rmpath(tempPath);
}

bool IEFile::doesFileExist(const QString& path)
{
    QFile file(path);
    return file.exists();
}

bool IEFile::doesPathExist(const QString& path)
{
    QString temp = removeFileName(path);

    QDir dir(temp);
    return dir.exists();
}

QString IEFile::absolutePath(const QString& path)
{
    QDir dir(path);

    return dir.absolutePath();
}

QString IEFile::extractPath(const QString& path)
{
    int index1 = path.lastIndexOf("/") + 1;
    int index2 = path.lastIndexOf("\\") + 1;
    int index = qMax(index1, index2);

    return path.mid(0, index);
}

QString IEFile::extractName(const QString& path)
{
    int index1 = path.lastIndexOf("/") + 1;
    int index2 = path.lastIndexOf("\\") + 1;
    int index3 = path.lastIndexOf(".");
    int index = qMax(index1, index2);

    return path.mid(index, index3 - index);
}

QString IEFile::extractExtension(const QString& path)
{
    int index = path.lastIndexOf('.');
    if(index < 0)
        return "";

    return path.mid(index);
}

QString IEFile::removeFileName(const QString& path)
{
    if(path.lastIndexOf(".") > 0)
    {
        const int index = path.lastIndexOf("/");
        return path.mid(0, index);
    }

    return path;
}
