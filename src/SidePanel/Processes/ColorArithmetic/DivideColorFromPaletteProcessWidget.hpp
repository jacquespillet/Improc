#pragma once
#include "SidePanel/BaseProcessWidget.hpp"

class DivideColorFromPaletteProcessWidget : public BaseProcessWidget {
Q_OBJECT
public:
    DivideColorFromPaletteProcessWidget(SidePanel *parent, uint32_t Index);
    ImProc::color_f32 Divisor;
    Vector4FEditor *DivisorEditor;    
signals:
  void Modified(int index);
};