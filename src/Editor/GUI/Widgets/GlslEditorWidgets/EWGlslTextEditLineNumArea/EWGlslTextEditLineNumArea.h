#pragma once

#include <QWidget>
#include <QPaintEvent>
#include <QColor>

class EWGlslPlainTextEdit;

class EWGlslTextEditLineNumArea : public QWidget
{
    // Does not own this pointer
    EWGlslPlainTextEdit* textEdit;

    QColor fillRectColor;
    QColor inactiveNumColor;
    QColor activeNumColor;

public:
    EWGlslTextEditLineNumArea(EWGlslPlainTextEdit* parent);
    ~EWGlslTextEditLineNumArea();

    QSize sizeHint() const;

    QColor getFillRectColor() { return fillRectColor; }
    QColor getInactiveNumColor() { return inactiveNumColor; }
    QColor getActiveNumColor() { return activeNumColor; }

protected:
    void paintEvent(QPaintEvent *event) override;
};

