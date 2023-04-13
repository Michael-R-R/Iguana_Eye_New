#include "EWGlslSyntaxHighlighter.h"
#include "GlslCollectionHighlight.h"
#include "GlslExpressionHighlight.h"

EWGlslSyntaxHighlighter::EWGlslSyntaxHighlighter(QTextDocument* parent) :
    QSyntaxHighlighter(parent),
    highlightingBehaviours()
{
    setupHighlightBehaviours();
}

EWGlslSyntaxHighlighter::~EWGlslSyntaxHighlighter()
{
    clearBehaviours();
}

void EWGlslSyntaxHighlighter::updateFormat(const int start, const int end, const QTextCharFormat& textFormat)
{
    this->setFormat(start, end, textFormat);
}

void EWGlslSyntaxHighlighter::updateCurrentBlockState(int state)
{
    this->setCurrentBlockState(state);
}

void EWGlslSyntaxHighlighter::highlightBlock(const QString& word)
{
    for(auto item : highlightingBehaviours)
    {
        item->processSyntax(word, this);
    }
}

void EWGlslSyntaxHighlighter::setupHighlightBehaviours()
{
    highlightingBehaviours.append(new GlslCollectionHighlight(QColor(82, 150, 236), "\\b[0-9A-Za-z_]+\\b", "./resources/syntax/glsl/glsl_dataType.txt"));
    highlightingBehaviours.append(new GlslCollectionHighlight(QColor(20, 144, 249), "\\b[0-9A-Za-z_]+\\b", "./resources/syntax/glsl/glsl_keywords.txt"));
    highlightingBehaviours.append(new GlslCollectionHighlight(QColor(144, 193, 255), "\\b[0-9A-Za-z_]+\\b", "./resources/syntax/glsl/glsl_variables.txt"));
    highlightingBehaviours.append(new GlslCollectionHighlight(QColor(226, 136, 60), "\\b[0-9A-Za-z_]+\\b", "./resources/syntax/glsl/glsl_functions.txt"));
    highlightingBehaviours.append(new GlslExpressionHighlight("\\b\\d+", "\\b\\d+", QColor(174, 246, 183)));
    highlightingBehaviours.append(new GlslExpressionHighlight("({)|(})|(\\()|(\\))", "({)|(})|(\\()|(\\))", QColor(250, 53, 101)));
    highlightingBehaviours.append(new GlslExpressionHighlight("#", "\\s+", QColor(235, 74, 210)));
    highlightingBehaviours.append(new GlslExpressionHighlight("//", "$", QColor(88, 205, 71)));
}

void EWGlslSyntaxHighlighter::clearBehaviours()
{
    for(SyntaxHighlightBehaviour* i : highlightingBehaviours)
    {
        delete i;
    }

    highlightingBehaviours.clear();
}
