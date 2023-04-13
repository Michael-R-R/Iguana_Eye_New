#pragma once

#include <QRegularExpression>

#include "SyntaxHighlightBehaviour.h"

class EWGlslSyntaxHighlighter;

class GlslExpressionHighlight : public SyntaxHighlightBehaviour
{
    QRegularExpression startExpression;
    QRegularExpression endExpression;

public:
    GlslExpressionHighlight(const QString& startExpr, const QString& endExpr, const QColor& color);
    ~GlslExpressionHighlight();

    void processSyntax(const QString& word, EWGlslSyntaxHighlighter* highlighter) override;

private:
    void processSpecialSyntax(const QString& word, EWGlslSyntaxHighlighter* highlighter);
};

