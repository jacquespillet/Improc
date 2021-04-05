#include "MainWindow.hpp"

#include "SidePanel/SidePanel.hpp"

MainWindow::MainWindow() {
    setWindowTitle("3D");
    
    view3D = new GL_View3D(this);
    setCentralWidget(view3D);

    Stack.NumProcesses=0;
    Stack.Processes=0;

    SidePanel* sidePanel = new SidePanel(this);
    sidePanel->Stack = &Stack;
    addDockWidget(Qt::RightDockWidgetArea, sidePanel);

    connect(sidePanel, &SidePanel::Modified, this, &MainWindow::Process);



    In = {};
    Out = {};
}

void MainWindow::Process()
{
    Width = view3D->size().width();
    Height = view3D->size().height();
    
    In = ImProc::EmptyImage(Width, Height);
    Out = ImProc::EmptyImage(Width, Height);

    ProcessStack(&In, &Out, Stack);
    
    view3D->SetImage(Out);
}

MainWindow::~MainWindow()
{
    DeallocateImage(&In);
    DeallocateImage(&Out);
}

void MainWindow::GetSize(uint32_t *Width, uint32_t *Height)
{
    this->Width = view3D->size().width();
    this->Height = view3D->size().height();

    *Width = this->Width;
    *Height = this->Height;
}