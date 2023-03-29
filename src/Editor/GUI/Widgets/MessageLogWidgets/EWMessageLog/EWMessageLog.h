#pragma once

#include <QPlainTextEdit>
#include <QTextCharFormat>

#include "IEObject.h"

class EWMessageLog : public QPlainTextEdit
{
    QTextCharFormat normalFormat;
    QTextCharFormat errorFormat;

public:
    EWMessageLog(QWidget* parent = nullptr);
    ~EWMessageLog();

    void toDisk(const QString& path);

public slots:
    void insertMessage(const QString& msg, const IEObject::MessageType type);
};

