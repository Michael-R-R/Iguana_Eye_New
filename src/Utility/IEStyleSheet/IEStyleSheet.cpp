#include "IEStyleSheet.h"
#include <QApplication>
#include <QWidget>
#include "IEFile.h"

void IEStyleSheet::setStyle(QApplication* app,
                                     const QString& styleVarsPath,
                                     const QString& styleSheetPath)
{
    QString style = textReplace(styleVarsPath, styleSheetPath);
    app->setStyleSheet(style);
}

void IEStyleSheet::setStyle(QWidget* widget,
                                     const QString& styleVarsPath,
                                     const QString& styleSheetPath)
{
    QString style = textReplace(styleVarsPath, styleSheetPath);
    widget->setStyleSheet(style);
}

QString IEStyleSheet::textReplace(const QString& styleVarsPath, const QString& styleSheetPath)
{
    QString varContent = "";
    QString styleContent = "";

    IEFile::read(styleVarsPath, &varContent);
    IEFile::read(styleSheetPath, &styleContent);

    QString tempLine = "";
    QString tempVar = "";
    QString tempVal = "";
    int prevIndex = 0;
    int currIndex = varContent.indexOf('\n') + 1;

    while(currIndex > 0)
    {
        tempLine = varContent.mid(prevIndex, currIndex - prevIndex);

        int delimIndex = tempLine.indexOf('=');
        tempVar = tempLine.mid(0, delimIndex - 1);
        tempVal = tempLine.mid(delimIndex + 2, (tempLine.size() - 1) - (delimIndex + 2));

        styleContent.replace(tempVar, tempVal);

        prevIndex = currIndex;
        currIndex = varContent.indexOf('\n', currIndex + 1) + 1;
    }

    return styleContent;
}
