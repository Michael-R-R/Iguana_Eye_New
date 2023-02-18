#include "EWGlslPlainTextEdit.h"
#include <QPainter>
#include <QTextBlock>

EWGlslPlainTextEdit::EWGlslPlainTextEdit(QWidget* parent) :
    QPlainTextEdit(parent),
    lineHighlightColor(32, 32, 32),
    lineNumWidget(new EWGlslTextEditLineNumArea(this))
{
    connect(this, &EWGlslPlainTextEdit::blockCountChanged, this, &EWGlslPlainTextEdit::updateLineNumberAreaWidth);
    connect(this, &EWGlslPlainTextEdit::updateRequest, this, &EWGlslPlainTextEdit::updateLineNumberArea);
    connect(this, &EWGlslPlainTextEdit::cursorPositionChanged, this, &EWGlslPlainTextEdit::highlightCurrentLine);
    this->updateLineNumberAreaWidth();
    this->highlightCurrentLine();
}

void EWGlslPlainTextEdit::lineNumberAreaPaintEvent(QPaintEvent* event)
{
    QPainter painter(lineNumWidget);

    painter.fillRect(event->rect(), lineNumWidget->getFillRectColor());

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while(block.isValid() && top <= event->rect().bottom())
    {
        if(block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);
            int textCursorBlockNum = textCursor().blockNumber();
            QColor penColor = (textCursorBlockNum == blockNumber) ? lineNumWidget->getActiveNumColor() : lineNumWidget->getInactiveNumColor();

            painter.setPen(penColor);
            painter.drawText(0, top, lineNumWidget->width(), fontMetrics().height(), Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());

        blockNumber++;
    }
}

int EWGlslPlainTextEdit::getLineNumAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while(max >= 10)
    {
        max /= 10;
        digits++;
    }

    int space = 12 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void EWGlslPlainTextEdit::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelect;

    if(!isReadOnly())
    {
        QTextEdit::ExtraSelection selection;

        selection.format.setBackground(lineHighlightColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);

        selection.cursor = textCursor();
        selection.cursor.clearSelection();

        extraSelect.append(selection);
    }

    setExtraSelections(extraSelect);
}

void EWGlslPlainTextEdit::updateLineNumberAreaWidth()
{
    setViewportMargins(getLineNumAreaWidth(), 0, 0, 0);
}

void EWGlslPlainTextEdit::updateLineNumberArea(const QRect& rect, int dy)
{
    if(dy)
        lineNumWidget->scroll(0, dy);
    else
        lineNumWidget->update(0, rect.y(), lineNumWidget->width(), rect.height());

    if(rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth();
}

void EWGlslPlainTextEdit::resizeEvent(QResizeEvent* event)
{
    QPlainTextEdit::resizeEvent(event);

    QRect rect = this->contentsRect();
    lineNumWidget->setGeometry(QRect(rect.left(), rect.top(), this->getLineNumAreaWidth(), rect.height()));
}
