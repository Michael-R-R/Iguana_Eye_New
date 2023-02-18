#pragma once

// Use the following website for testing regular expressions:
// https://rubular.com/

#include <QSyntaxHighlighter>
#include <QTextDocument>

class EWGlslSyntaxHighlighter : public QSyntaxHighlighter
{

public:
    EWGlslSyntaxHighlighter(QTextDocument* parent);
    ~EWGlslSyntaxHighlighter() {}

protected:
    void highlightBlock(const QString& text) override;
};

