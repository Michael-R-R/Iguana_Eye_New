#pragma once

#include <QTextCharFormat>
#include <QColor>

class EWGlslSyntaxHighlighter;

class SyntaxHighlightBehaviour
{
protected:
    QColor textColor;
    QTextCharFormat textFormat;

public:
    SyntaxHighlightBehaviour(const QColor& color);
    virtual ~SyntaxHighlightBehaviour();

    virtual void processSyntax(const QString& word, EWGlslSyntaxHighlighter* highlighter) = 0;
};

