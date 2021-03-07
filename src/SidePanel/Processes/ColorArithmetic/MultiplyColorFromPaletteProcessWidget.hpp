#pragma once
#include "SidePanel/BaseProcessWidget.hpp"

class MultiplyColorFromPaletteProcessWidget : public BaseProcessWidget {
Q_OBJECT
public:
    MultiplyColorFromPaletteProcessWidget(SidePanel *parent, uint32_t Index);
    ImProc::color_f32 Multiplier;
    Vector4FEditor *MultiplierEditor;
signals:
  void Modified(int index);
};