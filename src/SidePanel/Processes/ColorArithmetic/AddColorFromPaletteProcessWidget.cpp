#include "AddColorFromPaletteProcessWidget.hpp"


AddColorFromPaletteProcessWidget::AddColorFromPaletteProcessWidget(SidePanel *parent, uint32_t Index) : BaseProcessWidget("Add Color", parent, Index)
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


void SidePanel::AddColorProcessModified(uint32_t ModifiedIndex)
{
    std::pair<QWidget*, ImProc::process*> process = processes[ModifiedIndex];
    AddColorFromPaletteProcessWidget* Widget = (AddColorFromPaletteProcessWidget*)(process.first);
    ImProc::color_u8 Color = Widget->Color;
    process.second->AddColorProcess.Fields.Addend = Color;
    
    emit Modified();  
}


void SidePanel::CreateAddColorFromPaletteProcessWidget()
{
    uint32_t ProcessIndex = processes.size();

    AddColorFromPaletteProcessWidget *newProcessWidget = new AddColorFromPaletteProcessWidget(this, ProcessIndex);
    layout->addWidget(newProcessWidget);
    connect(newProcessWidget, &AddColorFromPaletteProcessWidget::Modified, this, &SidePanel::AddColorProcessModified);

    ImProc::process *ColorProcess = ImProc::CreateAddColorProcess(ImProc::ColorU8(0, 0, 0, 255));
    ColorProcess = AddProcess(Stack, (ImProc::process*)ColorProcess);      
    
    processes.push_back(std::make_pair((BaseProcessWidget*)newProcessWidget, ColorProcess));

    emit Modified();

    connect(newProcessWidget, &BaseProcessWidget::Remove, this, &SidePanel::RemoveProcess);
}
