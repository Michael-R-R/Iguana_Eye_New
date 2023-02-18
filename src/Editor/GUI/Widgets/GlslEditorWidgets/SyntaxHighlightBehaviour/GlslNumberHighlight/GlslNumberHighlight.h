#pragma once

#include "SyntaxHighlightBehaviour.h"

class GlslNumberHighlight : public SyntaxHighlightBehaviour
{

public:
    GlslNumberHighlight();
    ~GlslNumberHighlight() {}

    void processSyntax(const QString& word, EWGlslSyntaxHighlighter* highlighter) override;
};

