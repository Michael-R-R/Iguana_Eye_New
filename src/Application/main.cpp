#include "ApplicationWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    ApplicationWindow window;

    window.show();
    int execVal = application.exec();
    window.shutdown();

    return execVal;
}
