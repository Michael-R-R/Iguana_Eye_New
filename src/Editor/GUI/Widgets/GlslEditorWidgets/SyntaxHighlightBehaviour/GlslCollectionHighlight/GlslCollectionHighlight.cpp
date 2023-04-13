#include "GlslCollectionHighlight.h"
#include <QFile>
#include <QTextStream>
#include "EWGlslSyntaxHighlighter.h"

GlslCollectionHighlight::GlslCollectionHighlight(const QColor& color, const QString& expr, const QString& filePath) :
    SyntaxHighlightBehaviour(color),
    textSet(),
    expression(QRegularExpression(expr))
{
    openSyntaxFile(filePath);
}

GlslCollectionHighlight::~GlslCollectionHighlight()
{

}

void GlslCollectionHighlight::processSyntax(const QString& word, EWGlslSyntaxHighlighter* highlighter)
{
    QRegularExpressionMatchIterator it = expression.globalMatch(word);
    while(it.hasNext())
    {
        QRegularExpressionMatch match = it.next();
        if(!textSet.contains(match.captured(0)))
            continue;

        highlighter->updateFormat(match.capturedStart(), match.capturedLength(), textFormat);
    }
}

void GlslCollectionHighlight::openSyntaxFile(const QString& filePath)
{
    if(filePath.isEmpty())
        return;

    QFile inFile(filePath);
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

    inFile.close();
}
