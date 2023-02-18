#include "SyntaxHighlightBehaviour.h"
#include <QFile>
#include <QTextStream>
#include "EWGlslSyntaxHighlighter.h"

SyntaxHighlightBehaviour::SyntaxHighlightBehaviour(QColor color, const QString& syntaxFilePath) :
    textColor(color), textFormat(), textSet(),
    startExpression(), endExpression()
{
    textFormat.setFontWeight(QFont::Bold);
    textFormat.setForeground(QBrush(textColor));
    openSyntaxFile(syntaxFilePath);
}

void SyntaxHighlightBehaviour::processSpecialSyntax(const QString& word, EWGlslSyntaxHighlighter* highlighter)
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

void SyntaxHighlightBehaviour::openSyntaxFile(const QString& syntaxFilePath)
{
    if(syntaxFilePath.isEmpty())
        return;

    QFile inFile(syntaxFilePath);
    if(!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream inStream(&inFile);

    while(!inStream.atEnd())
    {
        QString line = inStream.readLine();
        if(line.isEmpty())
            continue;

        textSet << line.trimmed();
    }
}
