#include "GlslDataTypeHighlight.h"
#include "EWGlslSyntaxHighlighter.h"

GlslDataTypeHighlight::GlslDataTypeHighlight(const QString& syntaxFilePath) :
    SyntaxHighlightBehaviour(QColor(82, 150, 236), syntaxFilePath)
{
    startExpression = QRegularExpression("\\b[0-9A-Za-z_]+\\b");
}

void GlslDataTypeHighlight::processSyntax(const QString& word, EWGlslSyntaxHighlighter* highlighter)
{
    QRegularExpressionMatchIterator it = startExpression.globalMatch(word);
    while(it.hasNext())
    {
        QRegularExpressionMatch match = it.next();
        if(!textSet.contains(match.captured(0)))
            continue;

        highlighter->updateFormat(match.capturedStart(), match.capturedLength(), textFormat);
    }
}
