#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>

class InputContainer;

class SelectAppOptionsWidget : public QWidget
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
    SelectAppOptionsWidget(QWidget* parent = nullptr);
    ~SelectAppOptionsWidget();

    void setupGameGroupBox(InputContainer* input);
    void setupEditorGroupBox(InputContainer* input);
};

