#include "GlslNumberHighlight.h"
#include "EWGlslSyntaxHighlighter.h"

GlslNumberHighlight::GlslNumberHighlight() :
    SyntaxHighlightBehaviour(QColor(174, 246, 183), "")
{
    startExpression = QRegularExpression("\\b\\d+");
    endExpression = QRegularExpression("\\b\\d+");
}

void GlslNumberHighlight::processSyntax(const QString& word, EWGlslSyntaxHighlighter* highlighter)
{
    if(!word.contains(startExpression))
        return;

    processSpecialSyntax(word, highlighter);
}
