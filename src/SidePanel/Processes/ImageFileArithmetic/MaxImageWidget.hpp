#pragma once
#include "SidePanel/BaseProcessWidget.hpp"


class MaxImageWidget : public BaseProcessWidget {
Q_OBJECT
public:
    MaxImageWidget(SidePanel *parent, uint32_t Index);
    QString FileName;
signals:
  void Modified(int index);
};