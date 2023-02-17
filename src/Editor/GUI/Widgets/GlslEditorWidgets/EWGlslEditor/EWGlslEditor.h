#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QSplitter>

class EWGlslEditor : public QWidget
{
    QVBoxLayout* vMainLayout;
    QSplitter* vSplitter;
    QSplitter* hSplitter;
    bool isVerticalView;

public:
    EWGlslEditor(QWidget* parent = nullptr);
    ~EWGlslEditor() {}

public slots:
    void changeView();

private:
    void setup();
};

