#include "NodeMenu.h"
#include "NodeEditor.h"

#include "Nodes/BaseNodes.hpp"
#include "Nodes/OperationNodes.hpp"
#include "Nodes/ImageNodes.hpp"

NodeMenu::NodeMenu(NodeEditor *editor) : editor(editor)
{
    setMinimumWidth(300);

    setWindowFlags(Qt::WindowStaysOnTopHint);
    QVBoxLayout *layout = new QVBoxLayout();
    setLayout(layout);
    
    QPushButton *numberNodeButton = new QPushButton("Number");
    layout->addWidget(numberNodeButton);
    connect(numberNodeButton, &QPushButton::clicked, this, [this](bool value){
        NumberNode *node = new NumberNode(0, 0);
        AddNodeToScene(node);
    });
    
    QPushButton *FileNodeButton = new QPushButton("File");
    layout->addWidget(FileNodeButton);
    connect(FileNodeButton, &QPushButton::clicked, this, [this](bool value){
        FileNode *node = new FileNode(0, 0);
        AddNodeToScene(node);
    });

    //
    
    QPushButton *AddNodeButton = new QPushButton("Add");
    layout->addWidget(AddNodeButton);
    connect(AddNodeButton, &QPushButton::clicked, this, [this](bool value){
        AddNode *node = new AddNode(0, 0);
        AddNodeToScene(node);
    });
    
    QPushButton *SubtractNodeButton = new QPushButton("Subtract");
    layout->addWidget(SubtractNodeButton);
    connect(SubtractNodeButton, &QPushButton::clicked, this, [this](bool value){
        SubtractNode *node = new SubtractNode(0, 0);
        AddNodeToScene(node);
    });
    
    
    QPushButton *MultiplyNodeButton = new QPushButton("Multiply");
    layout->addWidget(MultiplyNodeButton);
    connect(MultiplyNodeButton, &QPushButton::clicked, this, [this](bool value){
        MultiplyNode *node = new MultiplyNode(0, 0);
        AddNodeToScene(node);
    });
    
    
    QPushButton *DivideNodeButton = new QPushButton("Divide");
    layout->addWidget(DivideNodeButton);
    connect(DivideNodeButton, &QPushButton::clicked, this, [this](bool value){
        DivideNode *node = new DivideNode(0, 0);
        AddNodeToScene(node);
    });
    
    
    QPushButton *DisplayNodeButton = new QPushButton("Display");
    layout->addWidget(DisplayNodeButton);
    connect(DisplayNodeButton, &QPushButton::clicked, this, [this](bool value){
        DisplayNode *node = new DisplayNode(0, 0);
        AddNodeToScene(node);
    });

    //
    
    QPushButton *ImageNodeButton = new QPushButton("Image");
    layout->addWidget(ImageNodeButton);
    connect(ImageNodeButton, &QPushButton::clicked, this, [this](bool value){
        ImageNode *node = new ImageNode(0, 0);
        AddNodeToScene(node);
    });
    
    QPushButton *DisplayImageNodeButton = new QPushButton("Display Image");
    layout->addWidget(DisplayImageNodeButton);
    connect(DisplayImageNodeButton, &QPushButton::clicked, this, [this](bool value){
        DisplayImageNode *node = new DisplayImageNode(0, 0);
        AddNodeToScene(node);
    });
}

void NodeMenu::AddNodeToScene(Node *node)
{
    QPoint middleScreen = QPoint(this->editor->width() * 0.5f, this->editor->height() * 0.5f);

    QPointF mousePositionScene = this->editor->mapToScene(this->editor->mapFromGlobal(middleScreen));
    node->setPos(mousePositionScene);
    node->editor = this->editor;
    
    
    this->editor->scene->addItem(node);
    this->editor->scene->update();

    this->editor->Nodes.push_back(node);
}