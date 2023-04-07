#include "IEFile.h"

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

bool IEFile::doesPathExist(const QString& path)
{
    QString tempPath = removeFileName(path);

    QDir dir(tempPath);
    return dir.exists();
}

QString IEFile::extractName(const QString& path)
{
    int index1 = path.lastIndexOf("/") + 1;
    int index2 = path.lastIndexOf("\\") + 1;
    int index = qMax(index1, index2);

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
