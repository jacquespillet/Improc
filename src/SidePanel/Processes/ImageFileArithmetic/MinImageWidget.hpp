#pragma once
#include "SidePanel/BaseProcessWidget.hpp"


class MinImageWidget : public BaseProcessWidget {
Q_OBJECT
public:
    MinImageWidget(SidePanel *parent, uint32_t Index);
    QString FileName;
signals:
  void Modified(int index);
};