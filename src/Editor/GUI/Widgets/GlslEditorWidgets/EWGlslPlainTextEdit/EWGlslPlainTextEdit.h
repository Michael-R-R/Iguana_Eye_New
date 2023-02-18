#pragma once

#include <QPlainTextEdit>
#include <QPaintEvent>
#include <QResizeEvent>

#include "EWGlslTextEditLineNumArea.h"

class EWGlslPlainTextEdit : public QPlainTextEdit
{
    Q_OBJECT

    QColor lineHighlightColor;
    EWGlslTextEditLineNumArea* lineNumWidget;

public:
    EWGlslPlainTextEdit(QWidget* parent = nullptr);
    ~EWGlslPlainTextEdit() {}

    void lineNumberAreaPaintEvent(QPaintEvent* event);
    int getLineNumAreaWidth();

private slots:
    void highlightCurrentLine();
    void updateLineNumberAreaWidth();
    void updateLineNumberArea(const QRect& rect, int dy);

protected:
    void resizeEvent(QResizeEvent* event) override;
};

