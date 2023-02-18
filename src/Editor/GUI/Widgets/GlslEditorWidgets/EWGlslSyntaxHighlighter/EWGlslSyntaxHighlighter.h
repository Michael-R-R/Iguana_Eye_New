#pragma once

// Use the following website for testing regular expressions:
// https://rubular.com/

#include <QSyntaxHighlighter>
#include <QTextDocument>
#include <QVector>

#include "SyntaxHighlightBehaviour.h"

class EWGlslSyntaxHighlighter : public QSyntaxHighlighter
{
    QVector<SyntaxHighlightBehaviour*> highlightingBehaviours;

public:
    EWGlslSyntaxHighlighter(QTextDocument* parent);
    ~EWGlslSyntaxHighlighter();

    void updateFormat(const int start, const int end, const QTextCharFormat& textFormat);
    void updateCurrentBlockState(int state);

protected:
    void highlightBlock(const QString& word) override;

private:
    void setupHighlightBehaviours();
    void clearBehaviours();
};

