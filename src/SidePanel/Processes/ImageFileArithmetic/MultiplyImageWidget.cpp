#include "MultiplyImageWidget.hpp"
#include "MainWindow.hpp"


MultiplyImageWidget::MultiplyImageWidget(SidePanel *parent, uint32_t Index) : BaseProcessWidget("Multiply Image From File", parent, Index)
{
    // fileName = QFileDialog::getOpenFileName(this,
    // tr("Open Image"), "/home/jana", tr("Image Files (*.png *.jpg *.bmp)"));

    QPushButton *addButton = new QPushButton("Browse...");
    layout->addWidget(addButton);
    connect(addButton, &QPushButton::clicked, this, [this](){
        QFileDialog Dialog(this);
        Dialog.setFileMode(QFileDialog::ExistingFiles);
        Dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
        Dialog.setViewMode(QFileDialog::Detail);
        QStringList FileNames;
        if (Dialog.exec())
            FileNames = Dialog.selectedFiles();
        
        if(FileNames.size() > 0)
        {
            this->FileName = FileNames[0];
            emit Modified(this->Index);
        }
    });
    
    this->Index = Index;
}




void SidePanel::CreateMultiplyImageWidget()
{
    uint32_t ProcessIndex = processes.size();

    MultiplyImageWidget *newProcessWidget = new MultiplyImageWidget(this, ProcessIndex);
    layout->addWidget(newProcessWidget);
    connect(newProcessWidget, &MultiplyImageWidget::Modified, this, &SidePanel::MultiplyImageProcessModified);

    MainWindow *mainWindow = (MainWindow*) this->parentWidget();
    uint32_t Width, Height;
    mainWindow->GetSize(&Width, &Height);

    ImProc::process *ImageProcess = ImProc::CreateMultiplyImageProcess("", Width, Height, true);
    ImageProcess = AddProcess(Stack, (ImProc::process*)ImageProcess);
    
    processes.push_back(std::make_pair((BaseProcessWidget*)newProcessWidget, ImageProcess));

    emit Modified();

    connect(newProcessWidget, &BaseProcessWidget::Remove, this, &SidePanel::RemoveProcess);
}


void SidePanel::MultiplyImageProcessModified(uint32_t ModifiedIndex)
{
    std::pair<QWidget*, ImProc::process*> process = processes[ModifiedIndex];
    MultiplyImageWidget* Widget = (MultiplyImageWidget*)(process.first);
    
    
    MainWindow *mainWindow = (MainWindow*) this->parentWidget();
    uint32_t Width, Height;
    mainWindow->GetSize(&Width, &Height);

	std::string tmpString = Widget->FileName.toStdString();
	const char* FileName = tmpString.c_str();
    UpdateFileMultiplyImageProcess(&process.second->MultiplyImageProcess, FileName, Width, Height);
    
    emit Modified();  
}
