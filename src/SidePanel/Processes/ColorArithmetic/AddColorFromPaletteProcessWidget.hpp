#pragma once
#include "SidePanel/BaseProcessWidget.hpp"


class AddColorFromPaletteProcessWidget : public BaseProcessWidget {
Q_OBJECT
public:
    AddColorFromPaletteProcessWidget(SidePanel *parent, uint32_t Index);
    ImProc::color_u8 Color;
signals:
  void Modified(int index);
};