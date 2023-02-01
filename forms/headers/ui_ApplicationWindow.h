/********************************************************************************
** Form generated from reading UI file 'ApplicationWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPLICATIONWINDOW_H
#define UI_APPLICATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ApplicationWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ApplicationWindow)
    {
        if (ApplicationWindow->objectName().isEmpty())
            ApplicationWindow->setObjectName(QString::fromUtf8("ApplicationWindow"));
        ApplicationWindow->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ApplicationWindow/ApplicationWindow/IguanaEye.png"), QSize(), QIcon::Normal, QIcon::Off);
        ApplicationWindow->setWindowIcon(icon);
        centralwidget = new QWidget(ApplicationWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        ApplicationWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ApplicationWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        ApplicationWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ApplicationWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ApplicationWindow->setStatusBar(statusbar);

        retranslateUi(ApplicationWindow);

        QMetaObject::connectSlotsByName(ApplicationWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ApplicationWindow)
    {
        ApplicationWindow->setWindowTitle(QCoreApplication::translate("ApplicationWindow", "Iguana Eye", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ApplicationWindow: public Ui_ApplicationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPLICATIONWINDOW_H
