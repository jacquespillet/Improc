#pragma once
#include "SidePanel/BaseProcessWidget.hpp"


class SubtractImageWidget : public BaseProcessWidget {
Q_OBJECT
public:
    SubtractImageWidget(SidePanel *parent, uint32_t Index);
    QString FileName;
signals:
  void Modified(int index);
};