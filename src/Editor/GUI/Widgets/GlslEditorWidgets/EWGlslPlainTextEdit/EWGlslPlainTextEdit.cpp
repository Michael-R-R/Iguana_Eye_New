#include "EWGlslPlainTextEdit.h"
#include <QPainter>
#include <QTextBlock>

EWGlslPlainTextEdit::EWGlslPlainTextEdit(QWidget* parent) :
    QPlainTextEdit(parent),
    syntaxHighlighter(new EWGlslSyntaxHighlighter(this->document())),
    lineHighlightColor(32, 32, 32),
    lineNumWidget(new EWGlslTextEditLineNumArea(this))
{
    this->setWordWrapMode(QTextOption::NoWrap);
    this->setTabStopDistance(20.0);
    this->setUndoRedoEnabled(true);

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

void EWGlslPlainTextEdit::insertTab(const int count)
{
    for(int i = 0; i < count; i++)
    {
        textCursor().insertText("\t");
    }
}

void EWGlslPlainTextEdit::insertText(const char* text)
{
    textCursor().insertText(text);
}

void EWGlslPlainTextEdit::moveCursorLeft(const unsigned count)
{
    QTextCursor cursor = textCursor();

    int pos = cursor.position();
    cursor.setPosition(pos - count);

    setTextCursor(cursor);
}

void EWGlslPlainTextEdit::moveCursorRight(const unsigned count)
{
    QTextCursor cursor = textCursor();

    int pos = cursor.position();
    cursor.setPosition(pos + count);

    setTextCursor(cursor);
}

void EWGlslPlainTextEdit::moveCursorToPosition(const unsigned pos)
{
    QTextCursor cursor = textCursor();
    cursor.setPosition(pos);
    setTextCursor(cursor);
}

void EWGlslPlainTextEdit::handleReturnPressed()
{
    int tabCount = fetchPrevLineTabCount();
    insertTab(tabCount);
}

void EWGlslPlainTextEdit::handleLeftParenPressed()
{
    insertText(")");
    moveCursorLeft(1);
}

void EWGlslPlainTextEdit::handleLeftBracketPressed()
{
    insertText("\n");
    insertText("\t");

    const int tabCount = fetchPrevLineTabCount();
    insertTab(tabCount);

    const int cursorRecallPos = textCursor().position();

    insertText("\n");
    insertTab(tabCount);
    insertText("}");

    moveCursorToPosition(cursorRecallPos);
}

int EWGlslPlainTextEdit::fetchPrevLineTabCount()
{
    QString text = fetchPrevLineText();

    int tabCount  = 0;
    int tabIndex = text.indexOf("\t", 0);

    while(tabIndex > -1)
    {
        tabCount++;
        tabIndex = text.indexOf("\t", tabIndex + 1);
    }

    return tabCount;
}

QString EWGlslPlainTextEdit::fetchPrevLineText()
{
    QTextCursor cursor = textCursor();

    const int cursorRecallPos = cursor.position();

    cursor.movePosition(QTextCursor::Up);
    cursor.movePosition(QTextCursor::EndOfLine);
    cursor.select(QTextCursor::LineUnderCursor);

    QString selectedText = cursor.selectedText();

    cursor.clearSelection();

    setTextCursor(cursor);
    moveCursorToPosition(cursorRecallPos);

    return selectedText;
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

void EWGlslPlainTextEdit::keyPressEvent(QKeyEvent* event)
{
    QPlainTextEdit::keyPressEvent(event);

    switch(event->key())
    {
    case Qt::Key_Return: { handleReturnPressed(); break;}
    case '(': { handleLeftParenPressed(); break;}
    case '{': { handleLeftBracketPressed(); break;}
    default: { break; }
    }
}
