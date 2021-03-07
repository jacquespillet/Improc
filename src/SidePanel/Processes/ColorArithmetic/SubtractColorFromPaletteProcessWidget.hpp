#pragma once
#include "SidePanel/BaseProcessWidget.hpp"

class SubtractColorFromPaletteProcessWidget : public BaseProcessWidget {
Q_OBJECT
public:
    SubtractColorFromPaletteProcessWidget(SidePanel *parent, uint32_t Index);
    ImProc::color_u8 Color;
signals:
  void Modified(int index);
};