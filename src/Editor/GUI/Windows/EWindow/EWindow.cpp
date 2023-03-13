#include "EWindow.h"
#include "IEFile.h"

EWindow::EWindow(QString title, QWidget* parent) :
    QDockWidget(title, parent),
    permenentTitle(title),
    tempTitle(permenentTitle),
    hasModifications(false),
    isActive(false)
{
    this->setAttribute(Qt::WA_QuitOnClose, false);
    this->setAllowedAreas(Qt::AllDockWidgetAreas);
    this->hide();
}

EWindow::~EWindow()
{

}

void EWindow::modifyTitle(const QString& text)
{
    tempTitle = (text.isEmpty()) ? permenentTitle : permenentTitle + " - " + text;
    this->setWindowTitle(tempTitle);
}

void EWindow::setModified(const bool isModified)
{
    hasModifications = isModified;

    auto lastIndex = tempTitle.length() - 1;

    if(isModified)
    {
        if(tempTitle[lastIndex] != '*')
            tempTitle.append("*");
    }
    else
    {
        if(tempTitle[lastIndex] == '*')
            tempTitle = tempTitle.mid(0, lastIndex);
    }

    this->setWindowTitle(tempTitle);
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
