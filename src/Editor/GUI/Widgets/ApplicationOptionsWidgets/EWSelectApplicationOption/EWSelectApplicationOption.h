#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>

class BaseInput;

class EWSelectApplicationOption : public QWidget
{
    Q_OBJECT

    QHBoxLayout* hMainLayout;

    QVBoxLayout* vOptionSelectLayout;
    QVBoxLayout* vContentAreaLayout;

    QGroupBox* gameGroupBox;
    QVBoxLayout* gameGroupLayout;

    QGroupBox* editorGroupBox;
    QVBoxLayout* editorGroupLayout;

    QWidget* contentWidget;

public:
    EWSelectApplicationOption(QWidget* parent = nullptr);
    ~EWSelectApplicationOption();

    void setupGameGroupBox(BaseInput* input);
    void setupEditorGroupBox(BaseInput* input);
};

