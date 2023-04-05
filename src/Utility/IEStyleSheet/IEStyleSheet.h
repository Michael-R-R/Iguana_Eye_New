#pragma once

#include <QString>

class QApplication;
class QWidget;

class IEStyleSheet
{
public:
    static void setStyle(QApplication* app,
                         const QString& styleVarsPath,
                         const QString& styleSheetPath);

    static void setStyle(QWidget* widget,
                         const QString& styleVarsPath,
                         const QString& styleSheetPath);

private:
    static QString textReplace(const QString& styleVarsPath,
                               const QString& styleSheetPath);
};

