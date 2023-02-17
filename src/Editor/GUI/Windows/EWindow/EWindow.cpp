#include "EWindow.h"
#include "IEFile.h"

EWindow::EWindow(QString title, QWidget* parent) :
    QDockWidget(title, parent),
    isActive(false)
{
    this->setAttribute(Qt::WA_QuitOnClose, false);
    this->setAllowedAreas(Qt::AllDockWidgetAreas);
    this->hide();
}

EWindow::~EWindow()
{

}

void EWindow::toggleVisibilty(bool status)
{
    if(status) { this->show(); }
    else { this->hide(); }
}

void EWindow::setStyleByString(const QString& style)
{
    this->setStyleSheet(style);
}

void EWindow::setStyleByFile(const QString& path)
{
    QString style = "";
    if(!IEFile::read(path, &style))
        return;

    this->setStyleSheet(style);
}

void EWindow::showEvent(QShowEvent* event)
{
    QDockWidget::showEvent(event);
    isActive = true;
}

void EWindow::closeEvent(QCloseEvent* event)
{
    QDockWidget::closeEvent(event);
    isActive = false;
}
