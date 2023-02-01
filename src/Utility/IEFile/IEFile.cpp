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
