#include "GlslExpressionHighlight.h"
#include "EWGlslSyntaxHighlighter.h"

GlslExpressionHighlight::GlslExpressionHighlight(const QString& startExpr, const QString& endExpr, const QColor& color) :
    SyntaxHighlightBehaviour(color),
    startExpression(QRegularExpression(startExpr)),
    endExpression(QRegularExpression(endExpr))
{

}

GlslExpressionHighlight::~GlslExpressionHighlight()
{

}

void GlslExpressionHighlight::processSyntax(const QString& word, EWGlslSyntaxHighlighter* highlighter)
{
    if(!word.contains(startExpression))
        return;

    processSpecialSyntax(word, highlighter);
}

void GlslExpressionHighlight::processSpecialSyntax(const QString& word, EWGlslSyntaxHighlighter* highlighter)
{
    highlighter->updateCurrentBlockState(0);

    int startIndex = word.indexOf(startExpression);
    while (startIndex >= 0)
    {
        QRegularExpressionMatch endMatch;
        int endIndex = word.indexOf(endExpression, startIndex, &endMatch);
        int syntaxLength = 0;

        // Match found
        if (endIndex > -1)
        {
            syntaxLength = endIndex - startIndex + endMatch.capturedLength();
        }
        // No match found
        else
        {
            highlighter->updateCurrentBlockState(1);
            syntaxLength = word.length() - startIndex;
        }

        // Color the word
        highlighter->updateFormat(startIndex, syntaxLength, textFormat);

        // Advance to the next set of word
        startIndex = word.indexOf(startExpression, startIndex + syntaxLength);
    }
}
