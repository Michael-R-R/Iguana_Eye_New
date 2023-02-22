#include "EWGlslSrcEditor.h"
#include "EWGlslPlainTextEdit.h"

EWGlslSrcEditor::EWGlslSrcEditor(const QString& title, QWidget* parent) :
    QWidget(parent),
    vMainLayout(new QVBoxLayout(this)),
    titleLabel(new QLabel(title, this)),
    textEdit(new EWGlslPlainTextEdit(this))
{
    vMainLayout->addWidget(titleLabel);
    vMainLayout->addWidget(textEdit);

    connect(textEdit, &EWGlslPlainTextEdit::modificationChanged, this, &EWGlslSrcEditor::modificationUpdated);
}

void EWGlslSrcEditor::clear()
{
    textEdit->clear();
    emit modified(false);
}

void EWGlslSrcEditor::setModifiedStatus(const bool val)
{
    textEdit->document()->setModified(val);
}

void EWGlslSrcEditor::setTextContent(const QString& text)
{
    textEdit->clear();
    textEdit->setPlainText(text);
}

QString EWGlslSrcEditor::getTextContent()
{
    return textEdit->toPlainText();
}

void EWGlslSrcEditor::modificationUpdated(bool val)
{
    emit modified(val);
}
