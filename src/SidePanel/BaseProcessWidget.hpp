#pragma once

#include "CommonIncludes.hpp"
#include "SidePanel.hpp"



class SelectColorButtonWidget : public QPushButton
{
    Q_OBJECT
public:
    SelectColorButtonWidget( QWidget* Parent, QColor Color );

    void SetColor( const QColor& Color );
    QColor Color;

public slots:
    void UpdateColor();
    void ChangeColor();

signals:
  void Modified();

};

class Vector4FEditor : public QGroupBox
{
    Q_OBJECT
public:
    Vector4FEditor(QWidget *Parent, QString widgetName, float _r=1.0f,float _g=1.0f,float _b=1.0f,float _a=1.0f);
    float r, g, b, a;
private:
    // QVBoxLayout *layout;
    QGridLayout *layout;
signals:
  void Modified();

};

class BaseProcessWidget : public QGroupBox {
Q_OBJECT
public:
    BaseProcessWidget(QString ProcessName, SidePanel *parent, uint32_t Index);
    uint32_t Index;
protected:
    QVBoxLayout *layout;

signals:
    void Remove(uint32_t Index);
};