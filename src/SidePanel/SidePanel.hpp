#pragma once

#include "CommonIncludes.hpp"
#include <tuple>
#include <vector>

class BaseProcessWidget;

class SidePanel : public QDockWidget {
  Q_OBJECT
  public:
      SidePanel(QWidget *parent);
      
      ImProc::processes_stack *Stack;
      std::vector<std::pair<BaseProcessWidget*, ImProc::process*>> processes;

  private:
  QVBoxLayout *layout;
  
  private slots:
    void ShowProcessesMenu();
    void RemoveProcess(uint32_t Index);

    void CreateAddColorFromPaletteProcessWidget();
    void AddColorProcessModified(uint32_t ModifiedIndex);
    
    void CreateSubtractColorFromPaletteProcessWidget();
    void SubtractColorProcessModified(uint32_t ModifiedIndex);
    
    void CreateMultiplyColorFromPaletteProcessWidget();
    void MultiplyColorProcessModified(uint32_t ModifiedIndex);
    
    void CreateDivideColorFromPaletteProcessWidget();
    void DivideColorProcessModified(uint32_t ModifiedIndex);
    


    void CreateAddImageWidget();
    void AddImageProcessModified(uint32_t ModifiedIndex);
    
    void CreateSubtractImageWidget();
    void SubtractImageProcessModified(uint32_t ModifiedIndex);
    
    void CreateMultiplyImageWidget();
    void MultiplyImageProcessModified(uint32_t ModifiedIndex);
    
    void CreateDivideImageWidget();
    void DivideImageProcessModified(uint32_t ModifiedIndex);
    
    void CreateMinImageWidget();
    void MinImageProcessModified(uint32_t ModifiedIndex);
    
    void CreateMaxImageWidget();
    void MaxImageProcessModified(uint32_t ModifiedIndex);
    


    void CreateLogarithmProcessWidget();
    void LogarithmProcessModified(uint32_t ModifiedIndex);

    void CreatePowerProcessWidget();
    void PowerProcessModified(uint32_t ModifiedIndex);

    void CreateNegateProcessWidget();
    void NegateProcessModified(uint32_t ModifiedIndex);

  signals:
    void Modified();
};