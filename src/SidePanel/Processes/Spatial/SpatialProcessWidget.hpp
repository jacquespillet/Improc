#pragma once
#include "SidePanel/BaseProcessWidget.hpp"


class LogarithmProcessWidget : public BaseProcessWidget {
Q_OBJECT
public:
    LogarithmProcessWidget(SidePanel *parent, uint32_t Index, float ConstantValue);
    float ConstantValue;
signals:
  void Modified(int index);
};

class NegateProcessWidget : public BaseProcessWidget {
Q_OBJECT
public:
    NegateProcessWidget(SidePanel *parent, uint32_t Index);
signals:
  void Modified(int index);
};

class PowerProcessWidget : public BaseProcessWidget {
Q_OBJECT
public:
    PowerProcessWidget(SidePanel *parent, uint32_t Index, float ConstantTerm, float ExponentTerm);
    float ConstantValue;
    float ExponentValue;
signals:
  void Modified(int index);
};