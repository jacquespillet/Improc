#pragma once
#include "SidePanel/BaseProcessWidget.hpp"


class AddImageWidget : public BaseProcessWidget {
Q_OBJECT
public:
    AddImageWidget(SidePanel *parent, uint32_t Index);
    QString FileName;
signals:
  void Modified(int index);
};