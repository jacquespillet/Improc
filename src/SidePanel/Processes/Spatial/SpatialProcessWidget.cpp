#include "SpatialProcessWidget.hpp"


LogarithmProcessWidget::LogarithmProcessWidget(SidePanel *parent, uint32_t Index, float ConstantValue) : BaseProcessWidget("Logarithm", parent, Index)
{
    this->Index = Index;
    this->ConstantValue = ConstantValue;
    

    QDoubleSpinBox *SpinBox = new QDoubleSpinBox(this);
    SpinBox->setValue((double)ConstantValue);
    SpinBox->setRange(0.0, 300.0);
    SpinBox->setSingleStep(0.05);
    
    connect(SpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double Value){
        this->ConstantValue = (float)Value;
        emit Modified(this->Index);
    });
    
    layout->addWidget(SpinBox);
}


void SidePanel::LogarithmProcessModified(uint32_t ModifiedIndex)
{
    std::pair<QWidget*, ImProc::process*> process = processes[ModifiedIndex];
    LogarithmProcessWidget* Widget = (LogarithmProcessWidget*)(process.first);
    process.second->LogarithmProcess.Fields.ConstantTerm = Widget->ConstantValue;
    
    emit Modified();  
}


void SidePanel::CreateLogarithmProcessWidget()
{
    uint32_t ProcessIndex = processes.size();

    float ConstantTerm = 1.0f;

    LogarithmProcessWidget *newProcessWidget = new LogarithmProcessWidget(this, ProcessIndex, ConstantTerm);
    newProcessWidget->ConstantValue = ConstantTerm;
    layout->addWidget(newProcessWidget);
    connect(newProcessWidget, &LogarithmProcessWidget::Modified, this, &SidePanel::LogarithmProcessModified);

    ImProc::process *LogarithmProcess = ImProc::CreateLogarithmProcess(ConstantTerm);
    LogarithmProcess = AddProcess(Stack, (ImProc::process*)LogarithmProcess);      
    
    processes.push_back(std::make_pair((BaseProcessWidget*)newProcessWidget, LogarithmProcess));

    emit Modified();

    connect(newProcessWidget, &BaseProcessWidget::Remove, this, &SidePanel::RemoveProcess);
}

///


PowerProcessWidget::PowerProcessWidget(SidePanel *parent, uint32_t Index, float ConstantTerm, float ExponentTerm) : BaseProcessWidget("Power", parent, Index)
{
    this->Index = Index;
    this->ConstantValue = ConstantTerm;
    this->ExponentValue = ExponentTerm;
    

    QDoubleSpinBox *ConstantSpinBox = new QDoubleSpinBox(this);
    ConstantSpinBox->setValue((double)ConstantValue);
    ConstantSpinBox->setRange(0.0, 300.0);
    ConstantSpinBox->setSingleStep(0.05);
    
    connect(ConstantSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double Value){
        this->ConstantValue = (float)Value;
        emit Modified(this->Index);
    });
    
    layout->addWidget(ConstantSpinBox);

    QDoubleSpinBox *ExponentSpinBox = new QDoubleSpinBox(this);
    ExponentSpinBox->setValue((double)ExponentValue);
    ExponentSpinBox->setRange(0.0, 300.0);
    ExponentSpinBox->setSingleStep(0.05);
    
    connect(ExponentSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double Value){
        this->ExponentValue = (float)Value;
        emit Modified(this->Index);
    });
    layout->addWidget(ExponentSpinBox);
    
}


void SidePanel::PowerProcessModified(uint32_t ModifiedIndex)
{
    std::pair<QWidget*, ImProc::process*> process = processes[ModifiedIndex];
    PowerProcessWidget* Widget = (PowerProcessWidget*)(process.first);
    process.second->PowerProcess.Fields.ConstantTerm = Widget->ConstantValue;
    process.second->PowerProcess.Fields.ExponentTerm = Widget->ExponentValue;
    
    emit Modified();  
}


void SidePanel::CreatePowerProcessWidget()
{
    float ConstantTerm = 1.0f;
    float ExponentTerm = 2.4f;

    uint32_t ProcessIndex = processes.size();

    PowerProcessWidget *newProcessWidget = new PowerProcessWidget(this, ProcessIndex, ConstantTerm, ExponentTerm);
    layout->addWidget(newProcessWidget);
    connect(newProcessWidget, &PowerProcessWidget::Modified, this, &SidePanel::PowerProcessModified);

    ImProc::process *PowerProcess = ImProc::CreatePowerProcess(ConstantTerm, ExponentTerm);
    PowerProcess = AddProcess(Stack, (ImProc::process*)PowerProcess);      
    
    processes.push_back(std::make_pair((BaseProcessWidget*)newProcessWidget, PowerProcess));

    emit Modified();

    connect(newProcessWidget, &BaseProcessWidget::Remove, this, &SidePanel::RemoveProcess);
}

//

NegateProcessWidget::NegateProcessWidget(SidePanel *parent, uint32_t Index) : BaseProcessWidget("Negate", parent, Index)
{
    this->Index = Index;
}


void SidePanel::NegateProcessModified(uint32_t ModifiedIndex)
{
    emit Modified();  
}


void SidePanel::CreateNegateProcessWidget()
{
    uint32_t ProcessIndex = processes.size();

    NegateProcessWidget *newProcessWidget = new NegateProcessWidget(this, ProcessIndex);
    layout->addWidget(newProcessWidget);
    connect(newProcessWidget, &NegateProcessWidget::Modified, this, &SidePanel::NegateProcessModified);

    ImProc::process *NegateProcess = ImProc::CreateNegateProcess();
    NegateProcess = AddProcess(Stack, (ImProc::process*)NegateProcess);      
    
    processes.push_back(std::make_pair((BaseProcessWidget*)newProcessWidget, NegateProcess));

    emit Modified();

    connect(newProcessWidget, &BaseProcessWidget::Remove, this, &SidePanel::RemoveProcess);
}
