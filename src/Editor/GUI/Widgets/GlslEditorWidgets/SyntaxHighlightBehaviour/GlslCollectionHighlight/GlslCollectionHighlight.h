#pragma once

#include <QSet>
#include <QRegularExpression>

#include "SyntaxHighlightBehaviour.h"

class GlslCollectionHighlight : public SyntaxHighlightBehaviour
{
    QSet<QString> textSet;
    QRegularExpression expression;

public:
    GlslCollectionHighlight(const QColor& color, const QString& expr, const QString& filePath);
    ~GlslCollectionHighlight();

    void processSyntax(const QString& word, EWGlslSyntaxHighlighter* highlighter) override;

private:
    void openSyntaxFile(const QString& filePath);
};

