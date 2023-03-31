#include "ApplicationWindow.h"

#include <QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QApplication application(argc, argv);
    ApplicationWindow window;

    window.startup();
    window.show();
    const int val = application.exec();
    window.shutdown();

    return val;
}
