#include "SidePanel.hpp"
#include "Processes/ColorArithmetic/AddColorFromPaletteProcessWidget.hpp"
#include "Processes/ImageFileArithmetic/AddImageWidget.hpp"
#include "Processes/ImageFileArithmetic/SubtractImageWidget.hpp"
#include "MainWindow.hpp"

#include "CurveEditor/CurveEditor.h"

SidePanel::SidePanel(QWidget *parent) : QDockWidget(parent) {
    setFeatures(QDockWidget::NoDockWidgetFeatures);
    
     QScrollArea *scrollArea = new QScrollArea(this);
     scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
     scrollArea->setWidgetResizable( true );
     scrollArea->setGeometry( 10, 10, 200, 200 );

     QWidget *widget = new QWidget();
     scrollArea->setWidget( widget );

     layout = new QVBoxLayout();
     layout->setAlignment(Qt::AlignTop);	
     widget->setLayout( layout );

     QPushButton *AddProcessButton = new QPushButton("Add Image Effect");
     layout->addWidget(AddProcessButton);
     connect(AddProcessButton, &QPushButton::pressed, this, &SidePanel::ShowProcessesMenu);
     setWidget(scrollArea);
    
    CurveEditor *Curve = new CurveEditor(nullptr);
    Curve->show();
    
}

void SidePanel::ShowProcessesMenu()
{
    QMenu myMenu;

    QMenu* UniformColorArithmeticMenu = new QMenu("Uniform Color Arithmetic");
    
    QAction *AddColorFromPaletteAction = UniformColorArithmeticMenu->addAction("Add Color From Palette");
    connect(AddColorFromPaletteAction, &QAction::triggered, this, &SidePanel::CreateAddColorFromPaletteProcessWidget);
    
    QAction *SubtractColorFromPaletteAction = UniformColorArithmeticMenu->addAction("Subtract Color From Palette");
    connect(SubtractColorFromPaletteAction, &QAction::triggered, this, &SidePanel::CreateSubtractColorFromPaletteProcessWidget);
    
    QAction *MultiplyColorFromPaletteAction = UniformColorArithmeticMenu->addAction("Multiply Color From Palette");
    connect(MultiplyColorFromPaletteAction, &QAction::triggered, this, &SidePanel::CreateMultiplyColorFromPaletteProcessWidget);
    
    QAction *DivideColorFromPaletteAction = UniformColorArithmeticMenu->addAction("Divide Color From Palette");
    connect(DivideColorFromPaletteAction, &QAction::triggered, this, &SidePanel::CreateDivideColorFromPaletteProcessWidget);

    QMenu* ImageArithmeticMenu = new QMenu("Image Arithmetic");
    QAction *AddImageAction = ImageArithmeticMenu->addAction("Add Image From File");
    connect(AddImageAction, &QAction::triggered, this, &SidePanel::CreateAddImageWidget);

    QAction *SubtractImageAction = ImageArithmeticMenu->addAction("Subtract Image From File");
    connect(SubtractImageAction, &QAction::triggered, this, &SidePanel::CreateSubtractImageWidget);

    QAction *MultiplyImageAction = ImageArithmeticMenu->addAction("Multiply Image From File");
    connect(MultiplyImageAction, &QAction::triggered, this, &SidePanel::CreateMultiplyImageWidget);

    QAction *DivideImageAction = ImageArithmeticMenu->addAction("Divide Image From File");
    connect(DivideImageAction, &QAction::triggered, this, &SidePanel::CreateDivideImageWidget);

    QAction *MinImageAction = ImageArithmeticMenu->addAction("Min Image From File");
    connect(MinImageAction, &QAction::triggered, this, &SidePanel::CreateMinImageWidget);

    QAction *MaxImageAction = ImageArithmeticMenu->addAction("Max Image From File");
    connect(MaxImageAction, &QAction::triggered, this, &SidePanel::CreateMaxImageWidget);

    QMenu* SpatialMenu = new QMenu("Spatial Processing");
    QAction *LogarithmAction = SpatialMenu->addAction("Logarithm");
    connect(LogarithmAction, &QAction::triggered, this, &SidePanel::CreateLogarithmProcessWidget);
    
    QAction *PowerAction = SpatialMenu->addAction("Power");
    connect(PowerAction, &QAction::triggered, this, &SidePanel::CreatePowerProcessWidget);
    
    QAction *NegateAction = SpatialMenu->addAction("Negate");
    connect(NegateAction, &QAction::triggered, this, &SidePanel::CreateNegateProcessWidget);

    
	myMenu.addMenu(UniformColorArithmeticMenu);
	myMenu.addMenu(ImageArithmeticMenu);
	myMenu.addMenu(SpatialMenu);

    QAction* selectedItem = myMenu.exec(QCursor::pos());
}


void SidePanel::RemoveProcess(uint32_t Index)
{
    BaseProcessWidget *WidgetToRemove  = processes[Index].first;
    ImProc::process *ProcessToRemove = processes[Index].second;


    layout->removeWidget(WidgetToRemove);
    delete WidgetToRemove;

    RemoveProcessFromStack(Stack, Index);

	processes.erase(processes.begin() + Index);

    for(int i=0; i<processes.size(); i++)
    {
        BaseProcessWidget *CurrentWidget  = processes[i].first;
        CurrentWidget->Index = i;
    }
    
    emit Modified();  
}