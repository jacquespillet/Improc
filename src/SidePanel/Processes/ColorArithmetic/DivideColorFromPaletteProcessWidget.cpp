#include "DivideColorFromPaletteProcessWidget.hpp"

DivideColorFromPaletteProcessWidget::DivideColorFromPaletteProcessWidget(SidePanel *parent, uint32_t Index) : BaseProcessWidget("Divide Color", parent, Index)
{
    this->Index = Index;

    
    DivisorEditor = new Vector4FEditor(this, "Divider");
    layout->addWidget(DivisorEditor);
    
    connect(DivisorEditor, &Vector4FEditor::Modified, this, [this](){
        Divisor = ImProc::ColorF32(DivisorEditor->r, DivisorEditor->g, DivisorEditor->b, DivisorEditor->a);
        emit Modified(this->Index);
    });
}


void SidePanel::CreateDivideColorFromPaletteProcessWidget()
{
    uint32_t ProcessIndex = processes.size();

    DivideColorFromPaletteProcessWidget *newProcessWidget = new DivideColorFromPaletteProcessWidget(this, ProcessIndex);
    layout->addWidget(newProcessWidget);
    connect(newProcessWidget, &DivideColorFromPaletteProcessWidget::Modified, this, &SidePanel::DivideColorProcessModified);

    ImProc::process *DivideColorProcess = ImProc::CreateDivideColorProcess(ImProc::ColorF32(1, 1, 1, 1));
    DivideColorProcess = AddProcess(Stack, (ImProc::process*)DivideColorProcess);      
    
    processes.push_back(std::make_pair((BaseProcessWidget*)newProcessWidget, DivideColorProcess));

    emit Modified();

    connect(newProcessWidget, &BaseProcessWidget::Remove, this, &SidePanel::RemoveProcess);
}


void SidePanel::DivideColorProcessModified(uint32_t ModifiedIndex)
{
    std::pair<QWidget*, ImProc::process*> process = processes[ModifiedIndex];
    DivideColorFromPaletteProcessWidget* Widget = (DivideColorFromPaletteProcessWidget*)(process.first);
    process.second->DivideColorProcess.Fields.Divisor = Widget->Divisor;
    
    emit Modified();  
}
