#include "SyntaxHighlightBehaviour.h"
#include "EWGlslSyntaxHighlighter.h"

SyntaxHighlightBehaviour::SyntaxHighlightBehaviour(const QColor& color) :
    textColor(color), textFormat()
{
    textFormat.setFontWeight(QFont::Bold);
    textFormat.setForeground(QBrush(textColor));
}

SyntaxHighlightBehaviour::~SyntaxHighlightBehaviour()
{

}
