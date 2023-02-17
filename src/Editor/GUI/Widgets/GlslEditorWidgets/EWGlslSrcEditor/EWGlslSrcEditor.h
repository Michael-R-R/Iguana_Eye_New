#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class EWGlslPlainTextEdit;

class EWGlslSrcEditor : public QWidget
{
    Q_OBJECT

    QVBoxLayout* vMainLayout;
    QLabel* titleLabel;
    EWGlslPlainTextEdit* textEdit;

public:
    EWGlslSrcEditor(const QString& title, QWidget* parent = nullptr);
    ~EWGlslSrcEditor() {}
};

