#pragma once

#include "SyntaxHighlightBehaviour.h"

class GlslDataTypeHighlight : public SyntaxHighlightBehaviour
{

public:
    GlslDataTypeHighlight(const QString& syntaxFilePath);
    ~GlslDataTypeHighlight() {}

    void processSyntax(const QString& word, EWGlslSyntaxHighlighter* highlighter) override;
};

