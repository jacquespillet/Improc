#include "BaseNodes.hpp"

#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QGraphicsProxyWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFileDialog>

#include "../Connection.h"

NumberNode::NumberNode(float X, float Y) : Node(0, 1, "Number")
{
    setPos(X, Y);

    value = new NumberData(0.0f);

    QDoubleSpinBox *spinBox = new QDoubleSpinBox();
	spinBox->setMaximumSize(spinBox->sizeHint());
    QObject::connect(spinBox, static_cast<void (QDoubleSpinBox::*)(double value)>(&QDoubleSpinBox::valueChanged), [this](double newValue){
        NumberData *numberValue = dynamic_cast<NumberData*>(this->value);
        numberValue->value = newValue;

        ComputeNext();
    });

	spinBox->setValue(0.0);
	spinBox->setMaximum(1000000000);
	spinBox->setMinimum(-1000000000);
	spinBox->setMaximumWidth(500);

    SetWidget(spinBox);
}

void NumberNode::Compute() 
{
	ComputeNext();
}


NodeData * NumberNode::GetValue()
{
    return dynamic_cast<NumberData*>(value);
}

//

FileNode::FileNode(float X, float Y) : Node(0, 1, "String")
{
    setPos(X, Y);

    value = new StringData("");

    QLineEdit *lineEdit = new QLineEdit();
	// lineEdit->setMaximumSize(lineEdit->sizeHint());
    QObject::connect(lineEdit, &QLineEdit::textChanged, [this](const QString &newValue){
        StringData *StringValue = dynamic_cast<StringData*>(this->value);
        StringValue->value = newValue;
        ComputeNext();
    });

    QPushButton *addButton = new QPushButton("Browse...");
    QObject::connect(addButton, &QPushButton::clicked, [this, lineEdit](){
        QFileDialog Dialog;
        Dialog.setFileMode(QFileDialog::ExistingFiles);
        Dialog.setNameFilter(QString("Images (*.png *.xpm *.jpg)"));
        Dialog.setViewMode(QFileDialog::Detail);
        QStringList FileNames;
        if (Dialog.exec())
            FileNames = Dialog.selectedFiles();
        
        if(FileNames.size() > 0)
        {
            StringData *StringValue = dynamic_cast<StringData*>(this->value);
            StringValue->value = FileNames[0];
            lineEdit->setText(FileNames[0]);
        }
    });

    QVBoxLayout *fileLayout = new QVBoxLayout();
    QWidget *fileWidget = new QWidget();
    fileWidget->setLayout(fileLayout);
    fileLayout->addWidget(lineEdit);
    fileLayout->addWidget(addButton);

    SetWidget(fileWidget);
    
    // QLineEdit *lineEdit2 = new QLineEdit();
	// // lineEdit->setMaximumSize(lineEdit->sizeHint());
    // QObject::connect(lineEdit2, &QLineEdit::textChanged, [this](const QString &newValue){
    //     StringData *StringValue = dynamic_cast<StringData*>(this->value);
    //     StringValue->value = newValue;
    //     ComputeNext();
    // });
    // AddWidget(lineEdit2);
}

void FileNode::Compute() 
{
	ComputeNext();
}


NodeData * FileNode::GetValue()
{
    return dynamic_cast<StringData*>(value);
}

//

DisplayNode::DisplayNode(float X, float Y) : Node(1, 0, "Display")
{
    value=nullptr;
    setPos(X, Y);

    textEdit = new QTextEdit();
    textEdit->setReadOnly(false);

    SetWidget(textEdit);
}

void DisplayNode::Compute() 
{
    if(inputConnections[0] == nullptr) return;

    Node *InputNode = inputConnections[0]->StartNode;

    NumberData *firstNumberValue = dynamic_cast<NumberData*>(InputNode->GetValue());
    if(firstNumberValue)
    {
        float numberValue = firstNumberValue->value; 
        QString stringValue = QString::number(numberValue);
        textEdit->setText(stringValue);
        return;
    }
}