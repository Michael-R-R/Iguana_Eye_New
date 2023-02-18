#include "EWGlslTextEditLineNumArea.h"
#include "EWGlslPlainTextEdit.h"

EWGlslTextEditLineNumArea::EWGlslTextEditLineNumArea(EWGlslPlainTextEdit* parent) :
    QWidget(parent),
    textEdit(parent),
    fillRectColor(32, 32, 32),
    inactiveNumColor(128, 128, 128),
    activeNumColor(90, 255, 30)
{

}

EWGlslTextEditLineNumArea::~EWGlslTextEditLineNumArea()
{
    textEdit = nullptr;
}

QSize EWGlslTextEditLineNumArea::sizeHint() const
{
    return QSize(textEdit->getLineNumAreaWidth(), 0);
}

void EWGlslTextEditLineNumArea::paintEvent(QPaintEvent* event)
{
    textEdit->lineNumberAreaPaintEvent(event);
}
