#pragma once

#include <QPlainTextEdit>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QKeyEvent>

#include "EWGlslSyntaxHighlighter.h"
#include "EWGlslTextEditLineNumArea.h"

class EWGlslPlainTextEdit : public QPlainTextEdit
{
    Q_OBJECT

    EWGlslSyntaxHighlighter* syntaxHighlighter;

    QColor lineHighlightColor;
    EWGlslTextEditLineNumArea* lineNumWidget;

public:
    EWGlslPlainTextEdit(QWidget* parent = nullptr);
    ~EWGlslPlainTextEdit() {}

    void lineNumberAreaPaintEvent(QPaintEvent* event);
    int getLineNumAreaWidth();

    void insertTab(const int count);
    void insertText(const char* text);
    void moveCursorLeft(const unsigned count);
    void moveCursorRight(const unsigned count);
    void moveCursorToPosition(const unsigned pos);

private:
    void handleReturnPressed();
    void handleLeftParenPressed();
    void handleLeftBracketPressed();

    int fetchPrevLineTabCount();
    QString fetchPrevLineText();

private slots:
    void highlightCurrentLine();
    void updateLineNumberAreaWidth();
    void updateLineNumberArea(const QRect& rect, int dy);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
};

