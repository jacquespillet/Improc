#pragma once
#include "SidePanel/BaseProcessWidget.hpp"


class DivideImageWidget : public BaseProcessWidget {
Q_OBJECT
public:
    DivideImageWidget(SidePanel *parent, uint32_t Index);
    QString FileName;
signals:
  void Modified(int index);
};