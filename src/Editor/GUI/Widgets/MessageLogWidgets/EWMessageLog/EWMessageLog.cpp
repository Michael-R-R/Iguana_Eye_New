#include "EWMessageLog.h"
#include "IEFile.h"
#include <QDateTime>

EWMessageLog::EWMessageLog(QWidget* parent) :
    QPlainTextEdit(parent),
    normalFormat(),
    errorFormat()
{
    this->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    this->setLineWrapMode(QPlainTextEdit::LineWrapMode::NoWrap);
    this->setReadOnly(true);

    normalFormat.setForeground(Qt::black);
    errorFormat.setForeground(Qt::red);
}

EWMessageLog::~EWMessageLog()
{

}

void EWMessageLog::toDisk(const QString& path)
{
    IEFile::write(path, this->toPlainText());
}

void EWMessageLog::insertMessage(const QString& msg, const IEObject::MessageType type)
{
    QTextCursor logCursor = this->textCursor();

    logCursor.insertText(QString("%1: ").arg(QDateTime::currentDateTime().toString()), normalFormat);

    switch(type)
    {
    case IEObject::MessageType::Normal: { logCursor.insertText(QString("%2\n").arg(msg), normalFormat); break; }
    case IEObject::MessageType::Error: { logCursor.insertText(QString("%2\n").arg(msg), errorFormat); break; }
    default: { break; }
    }
}
