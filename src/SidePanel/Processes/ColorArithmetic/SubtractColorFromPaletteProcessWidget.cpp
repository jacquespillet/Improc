#include "SubtractColorFromPaletteProcessWidget.hpp"


SubtractColorFromPaletteProcessWidget::SubtractColorFromPaletteProcessWidget(SidePanel *parent, uint32_t Index) : BaseProcessWidget("Subtract Color", parent, Index)
{
    this->Index = Index;

    SelectColorButtonWidget *button = new SelectColorButtonWidget(this, Qt::black);    
    connect(button, &SelectColorButtonWidget::Modified, this, [this, button](){
        QColor qColor = button->Color;
        Color = ImProc::ColorU8((uint8_t)qColor.red(), (uint8_t)qColor.green(), (uint8_t)qColor.blue(), (uint8_t)qColor.alpha());
        emit Modified(this->Index);
    });

    layout->addWidget(button);
}


void SidePanel::CreateSubtractColorFromPaletteProcessWidget()
{
    uint32_t ProcessIndex = processes.size();

    SubtractColorFromPaletteProcessWidget *newProcessWidget = new SubtractColorFromPaletteProcessWidget(this, ProcessIndex);
    layout->addWidget(newProcessWidget);
    connect(newProcessWidget, &SubtractColorFromPaletteProcessWidget::Modified, this, &SidePanel::SubtractColorProcessModified);

    ImProc::process *SubtractColorProcess = ImProc::CreateSubtractColorProcess(ImProc::ColorU8(0, 0, 0, 255));
    SubtractColorProcess = AddProcess(Stack, (ImProc::process*)SubtractColorProcess);      
    
    processes.push_back(std::make_pair((BaseProcessWidget*)newProcessWidget, SubtractColorProcess));

    emit Modified();

    connect(newProcessWidget, &BaseProcessWidget::Remove, this, &SidePanel::RemoveProcess);
}


void SidePanel::SubtractColorProcessModified(uint32_t ModifiedIndex)
{
    std::pair<QWidget*, ImProc::process*> process = processes[ModifiedIndex];
    SubtractColorFromPaletteProcessWidget* Widget = (SubtractColorFromPaletteProcessWidget*)(process.first);
    ImProc::color_u8 Color = Widget->Color;
    process.second->SubtractColorProcess.Fields.Subtrahend = Color;
    
    emit Modified();  
}

