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
