#include "Node.h"
#include <algorithm>

#include <QGraphicsSceneMouseEvent>
#include <QtWidgets/QGraphicsProxyWidget>
#include <QtGui/QPalette> 
#include <iostream>
#include "../NodeEditor.h"

Node::Node(uint8_t inputs, uint8_t outputs, QString Name) : inputs(inputs), outputs(outputs), name(Name) {
    nodeBrush = QBrush(Qt::darkBlue);
    nodeSelectedBrush = QBrush(Qt::blue);
    inputOutputBrush = QBrush(Qt::darkYellow);
    textBrush = QBrush(Qt::white);

    width = NODE_WIDTH;
    height = HEADER_SIZE + std::max(inputs, outputs) * (CONNECTION_SIZE + CONNECTION_SPACING);

    ComputeInputOutputPositions();

    inputConnections.resize(inputs);
    outputConnections.resize(outputs);

    proxy = new QGraphicsProxyWidget(this);

    setFlag(QGraphicsItem::ItemIsSelectable);
}

Node::~Node()
{
    std::cout << "DELETING" << std::endl;
    delete value;
}

void Node::ComputeInputOutputPositions()
{
	if (mainWidget != nullptr)
	{
	    mainWidget->updateGeometry();
		//QRectF geometry = mainWidget->geometry();
		width = std::max(width, (float)mainWidget->).width());
		height = std::max(height, HEADER_SIZE + (float)mainWidget->).height());
	}
    
    inputPositions.resize(inputs);
    float px = -CONNECTION_SIZE * 0.5f;
    float py = HEADER_SIZE;
    for(int i=0; i<inputs; i++)
    {
        inputPositions[i] = QPointF(px, py);
        py += CONNECTION_SPACING + CONNECTION_SIZE;
    }
    
    outputPositions.resize(outputs);
    px = width - CONNECTION_SIZE * 0.5f;
    py = HEADER_SIZE;
    for(int i=0; i<outputs; i++)
    {
        outputPositions[i] = QPointF(px, py);
        py += CONNECTION_SPACING + CONNECTION_SIZE;
    }
}

QRectF Node::boundingRect() const
{
    return BoundingRectangle;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    DrawNode(painter);
    DrawInputs(painter);
    DrawOutputs(painter);    
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    clickedPos = mapFromScene(event->scenePos()); 
    clicked=true;
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    clickedPos=QPointF(0,0);
    clicked=false;
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // if(clicked)
    // {
    //     setPos(event->scenePos() - clickedPos);
    // }
}


void Node::DrawNode(QPainter *painter)
{
    BoundingRectangle = QRectF(-CONNECTION_SIZE * 0.5f, 0, width + CONNECTION_SIZE, height);

    if(isSelected())
    {
        painter->setBrush(nodeSelectedBrush);
    }
    else
    {
        painter->setBrush(nodeBrush);
    }

    QRectF rectangle(0, 0, width, height);
    painter->drawRect(rectangle);

    painter->setPen(Qt::yellow);
    painter->drawText(QRectF(0, 0, width, HEADER_SIZE),Qt::AlignCenter, this->name);
}

void Node::DrawInputs(QPainter *painter)
{
    painter->setBrush(inputOutputBrush);
    for(int i=0; i<inputs; i++)
    {
        QPointF pos = inputPositions[i];
        painter->drawEllipse(pos.x(), pos.y(), 10, 10);
    }
}

void Node::DrawOutputs(QPainter *painter)
{
    painter->setBrush(inputOutputBrush);
    for(int i=0; i<outputs; i++)
    {
        QPointF pos = outputPositions[i];
        painter->drawEllipse(pos.x(), pos.y(), 10, 10);
    }
}


int8_t Node::CheckInputConnection(QPointF position)
{
    int8_t inputClickedIindex= -1;
    
    for(int i=0; i<inputs; i++)
    {
        QPointF pos = inputPositions[i];
        QLineF line(pos, mapFromScene(position));
        if(line.length() < CONNECTION_SIZE * 1.5f)
        {
            inputClickedIindex=i;
            break;
        }
    }

    return inputClickedIindex;
}

int8_t Node::CheckOutputConnection(QPointF position)
{
    int8_t outputClickedIindex= -1;
    
    for(int i=0; i<outputs; i++)
    {
        QPointF pos = outputPositions[i];
        QLineF line(pos, mapFromScene(position));
        if(line.length() < CONNECTION_SIZE * 1.5f)
        {
            outputClickedIindex=i;
            break;
        }
    }

    return outputClickedIindex;
}

QPointF Node::GetInputPosition(uint8_t inputIndex)
{
    return inputPositions[inputIndex];
}

QPointF Node::GetOutputPosition(uint8_t outputIndex)
{
    return outputPositions[outputIndex];
}

QPointF Node::GetInputPositionScene(uint8_t inputIndex)
{
    return mapToScene(inputPositions[inputIndex]);
}

QPointF Node::GetOutputPositionScene(uint8_t outputIndex)
{
    return mapToScene(outputPositions[outputIndex]);
}

void Node::Compute() {}

NodeData * Node::GetValue()
{
    return nullptr;
}

void Node::ComputeNext()
{
	for (int i = 0; i < outputConnections[0].size(); i++)
	{
		outputConnections[0][i]->EndNode->Compute();
	}
}


void Node::eraseInputConnection(Connection *connection)
{
    for(int i=inputConnections.size()-1; i>=0; i--)
    {
        if(inputConnections[i] == connection)
        {
            inputConnections[i] = nullptr;
        }
    }
}

void Node::eraseOutputConnection(Connection *connection)
{
    for(int i=0; i<outputConnections.size(); i++)
    {
        for(int j=outputConnections[i].size()-1; j>=0; j--)
        {
            if(outputConnections[i][j] == connection)
            {
                outputConnections[i].erase(outputConnections[i].begin() + i);
            }
        }
    }
}

void Node::SetWidget(QWidget *widget)
{
    mainWidget = new QWidget();
	mainWidget->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

    layout = new QVBoxLayout(mainWidget);
    layout->addWidget(widget);

    proxy->setWidget(mainWidget);
    proxy->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);


    ComputeInputOutputPositions();

    proxy->setPos(0, HEADER_SIZE);    

    QPalette pal;
    // set black background 
    pal.setColor(QPalette::Background, Qt::black); 
    mainWidget->setAutoFillBackground(true); 
    mainWidget->setPalette(pal); 
}

void Node::AddWidget(QWidget *widget)
{
    layout->addWidget(widget);

    ComputeInputOutputPositions();
    proxy->setPos(0, HEADER_SIZE);    
}

//





