#pragma once
#include "SidePanel/BaseProcessWidget.hpp"


class MultiplyImageWidget : public BaseProcessWidget {
Q_OBJECT
public:
    MultiplyImageWidget(SidePanel *parent, uint32_t Index);
    QString FileName;
signals:
  void Modified(int index);
};