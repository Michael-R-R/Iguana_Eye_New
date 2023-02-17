#pragma once

#include <QComboBox>

class AppStartEvent;

class EWShaderComboBox : public QComboBox
{
    Q_OBJECT

public:
    EWShaderComboBox(QWidget* parent = nullptr);
    ~EWShaderComboBox() {}

    void startup(const AppStartEvent& event);
};

