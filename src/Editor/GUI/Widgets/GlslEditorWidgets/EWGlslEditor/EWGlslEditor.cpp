#include "EWGlslEditor.h"

EWGlslEditor::EWGlslEditor(QWidget* parent) :
    QWidget(parent),
    vMainLayout(new QVBoxLayout(this)),
    vSplitter(new QSplitter(Qt::Vertical, this)),
    hSplitter(new QSplitter(this)),
    isVerticalView(true)
{

}

void EWGlslEditor::changeView()
{
    // TODO implement
    if(isVerticalView)
    {
        //hSplitter->addWidget(vTextEdit);
        //hSplitter->addWidget(fTextEdit);
    }
    else
    {
        //vSplitter->addWidget(1, vTextEdit);
        //vSplitter->addWidget(2, fTextEdit);
    }

    isVerticalView = !isVerticalView;
}

void EWGlslEditor::setup()
{
    vMainLayout->addWidget(vSplitter);

    vSplitter->addWidget(hSplitter);
}
