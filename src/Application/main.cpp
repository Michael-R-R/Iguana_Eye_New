#include <QApplication>
#include <QCoreApplication>

#include "ApplicationWindow.h"
#include "IEStyleSheet.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

    QApplication application(argc, argv);
    IEStyleSheet::setStyle(&application, "./resources/style/stylevars.qss", "./resources/style/stylesheet.qss");

    ApplicationWindow& window = ApplicationWindow::instance();
    window.init();
    window.show();
    const int val = application.exec();
    window.shutdown();

    return val;
}
