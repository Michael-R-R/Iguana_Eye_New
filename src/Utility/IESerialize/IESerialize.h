#pragma once

#include <QDataStream>
#include <QFile>
#include <QString>

#include "IEFile.h"

class IESerialize
{
    static inline QDataStream::Version qtVersion = QDataStream::Qt_6_3;
    static inline int masterFormat = 0x00000001;
    static inline int masterVersion = 1;

public:
    template<class T>
    static bool write(const QString& path, const T* data)
    {
        if(!data) { return false; }

        QFile outFile(path);
        if(!outFile.open(QIODevice::WriteOnly))
            return false;

        QDataStream outStream(&outFile);

        // Write a version header
        outStream << masterFormat;
        outStream << masterVersion;

        outStream.setVersion(qtVersion);

        outStream << *data;

        outFile.close();

        return true;
    }

    template<class T>
    static bool read(const QString& path, T* data)
    {
        if(!data) { return false; }

        QFile inFile(path);
        if(!inFile.open(QIODevice::ReadOnly))
            return false;

        QDataStream inStream(&inFile);

        // Check the version header
        int format = -1;
        inStream >> format;
        if(format != masterFormat)
            return false;

        int version = -1;
        inStream >> version;
        if(version != masterVersion)
            return false;

        inStream.setVersion(qtVersion);

        inStream >> *data;

        inFile.close();

        return true;
    }
};

