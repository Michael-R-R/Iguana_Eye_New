#pragma once

#include <QTextCharFormat>
#include <QColor>
#include <QSet>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>

class EWGlslSyntaxHighlighter;

class SyntaxHighlightBehaviour
{
protected:
    QColor textColor;
    QTextCharFormat textFormat;
    QSet<QString> textSet;

    QRegularExpression startExpression;
    QRegularExpression endExpression;

public:
    SyntaxHighlightBehaviour(QColor color, const QString& syntaxFilePath);
    ~SyntaxHighlightBehaviour() {}

    virtual void processSyntax(const QString& word, EWGlslSyntaxHighlighter* highlighter) = 0;

protected:
    virtual void processSpecialSyntax(const QString& word, EWGlslSyntaxHighlighter* highlighter);

private:
    void openSyntaxFile(const QString& syntaxFilePath);
};

