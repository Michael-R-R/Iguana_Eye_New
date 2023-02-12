#include "ApplicationWindow.h"

#include <QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QApplication application(argc, argv);
    ApplicationWindow window;

    window.show();
    int execVal = application.exec();
    window.shutdown();

    return execVal;
}
