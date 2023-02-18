#include "EWGlslSyntaxHighlighter.h"
#include "GlslDataTypeHighlight.h"
#include "GlslNumberHighlight.h"

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
    highlightingBehaviours.append(new GlslDataTypeHighlight(":/syntax/glsl_dataType.txt"));
    highlightingBehaviours.append(new GlslNumberHighlight());
}

void EWGlslSyntaxHighlighter::clearBehaviours()
{
    for(auto item : highlightingBehaviours)
    {
        auto temp = item;
        item = nullptr;
        delete temp;
    }

    highlightingBehaviours.clear();
}
