#pragma once

#include <QComboBox>
#include <QVector>

class AppStartEvent;
class IENameManager;
class IEShaderManager;

class EWShaderComboBox : public QComboBox
{
    Q_OBJECT

    // Does not own these pointers
    const IENameManager* nameManager;
    const IEShaderManager* shaderManager;

    QVector<unsigned long long> fullIdList;

public:
    EWShaderComboBox(QWidget* parent = nullptr);
    ~EWShaderComboBox();

    void startup(const AppStartEvent& event);
    void selectShader(const unsigned long long key);

private:
    bool indexBoundCheck(const int index);
    bool doesExist(const unsigned long long key);

private slots:
    void currentShaderChanged(int index);
    void addShader(const unsigned long long key);
    void removeShader(const unsigned long long key);
    void changeShaderKey(const unsigned long long oldKey, const unsigned long long newKey);

signals:
    void cleared();
    void vertexSrcSelected(const QString& vSrc);
    void fragmentSrcSelected(const QString& fSrc);
};

