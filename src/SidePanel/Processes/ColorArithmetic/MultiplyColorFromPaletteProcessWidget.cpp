#include "MultiplyColorFromPaletteProcessWidget.hpp"

MultiplyColorFromPaletteProcessWidget::MultiplyColorFromPaletteProcessWidget(SidePanel *parent, uint32_t Index) : BaseProcessWidget("Multiply Color", parent, Index)
{
    this->Index = Index;

    
    MultiplierEditor = new Vector4FEditor(this, "Multiplier");
    layout->addWidget(MultiplierEditor);
    
    connect(MultiplierEditor, &Vector4FEditor::Modified, this, [this](){
        Multiplier = ImProc::ColorF32(MultiplierEditor->r, MultiplierEditor->g, MultiplierEditor->b, MultiplierEditor->a);
        emit Modified(this->Index);
    });
}


void SidePanel::CreateMultiplyColorFromPaletteProcessWidget()
{
    uint32_t ProcessIndex = processes.size();

    MultiplyColorFromPaletteProcessWidget *newProcessWidget = new MultiplyColorFromPaletteProcessWidget(this, ProcessIndex);
    layout->addWidget(newProcessWidget);
    connect(newProcessWidget, &MultiplyColorFromPaletteProcessWidget::Modified, this, &SidePanel::MultiplyColorProcessModified);

    ImProc::process *MultiplyColorProcess = ImProc::CreateMultiplyColorProcess(ImProc::ColorF32(1, 1, 1, 1));
    MultiplyColorProcess = AddProcess(Stack, (ImProc::process*)MultiplyColorProcess);      
    
    processes.push_back(std::make_pair((BaseProcessWidget*)newProcessWidget, MultiplyColorProcess));

    emit Modified();

    connect(newProcessWidget, &BaseProcessWidget::Remove, this, &SidePanel::RemoveProcess);
}


void SidePanel::MultiplyColorProcessModified(uint32_t ModifiedIndex)
{
    std::pair<QWidget*, ImProc::process*> process = processes[ModifiedIndex];
    MultiplyColorFromPaletteProcessWidget* Widget = (MultiplyColorFromPaletteProcessWidget*)(process.first);
    process.second->MultiplyColorProcess.Fields.Multiplier = Widget->Multiplier;
    emit Modified();  
}
