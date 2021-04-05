#include "Connection.h"
#include <iostream>

Connection::Connection()
{
    StartNode = nullptr;
    EndNode = nullptr;

    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    setVisible(true);
    setEnabled(true);
}

QRectF Connection::boundingRect() const
{
    return boundingBox;
}

void Connection::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	if(isSelected())
    {
        painter->setPen(selectedPen);
    }
    else
    {
        painter->setPen(nonSelectedPen);
    }
    QPainterPath path;

    if(!finished)
    {
        QPointF StartPos;
        if(StartNode != nullptr)
        {
            StartPos = mapFromScene(StartNode->GetOutputPositionScene(StartIndex)) + QPointF(CONNECTION_SIZE * 0.5f, CONNECTION_SIZE *  0.5f);
        }
        else if(EndNode != nullptr)
        {
            StartPos = mapFromScene(EndNode->GetInputPositionScene(EndIndex)) + QPointF(CONNECTION_SIZE * 0.5f, CONNECTION_SIZE *  0.5f);;
        }

        path.moveTo(StartPos);
        path.lineTo(CurrentPosition);

        boundingBox = QRectF(StartPos, CurrentPosition);
    }
    else
    {
        QPointF StartPos = mapFromScene(StartNode->GetOutputPositionScene(StartIndex)) + QPointF(CONNECTION_SIZE * 0.5f, CONNECTION_SIZE *  0.5f);
        QPointF EndPos = mapFromScene(EndNode->GetInputPositionScene(EndIndex)) + QPointF(CONNECTION_SIZE * 0.5f, CONNECTION_SIZE *  0.5f);
        boundingBox = QRectF(StartPos, EndPos);
        path.moveTo(StartPos);
        path.lineTo(EndPos);
    }

    painter->drawPath(path);

}

Connection::Connection(Node *node, bool isInput, int index)
{
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    setVisible(true);
    setEnabled(true);

    selectedPen = QPen(Qt::darkGreen, 3);
    nonSelectedPen = QPen(Qt::green, 3);
    
    if(isInput)
    {
        EndNode = node;
        EndIndex = index;
		StartNode = nullptr;
    }
    else
    {
        StartNode = node;
        StartIndex = index;
		EndNode = nullptr;
    }
}

bool Connection::FinishConnection(Node *node, bool isInput, int index)
{
    if(isInput)
    {
        EndNode = node;
        EndIndex = index;
    }
    else
    {
        StartNode = node;
        StartIndex = index;
    }

    //In case we have created a connection between 2 start or 2 end points, one of the node will be null --> wrong
    if(StartNode == nullptr || EndNode == nullptr) return false;

    StartNode->outputConnections[StartIndex].push_back(this);
    EndNode->inputConnections[EndIndex] = this;

    finished=true;

    
    QPointF StartPos = mapFromScene(StartNode->GetOutputPositionScene(StartIndex)) + QPointF(CONNECTION_SIZE * 0.5f, CONNECTION_SIZE *  0.5f);
    QPointF EndPos = mapFromScene(EndNode->GetInputPositionScene(EndIndex)) + QPointF(CONNECTION_SIZE * 0.5f, CONNECTION_SIZE *  0.5f);
    boundingBox = QRectF(StartPos, EndPos);

    return true;
}

void Connection::SetCurrentPosition(QPointF position)
{
    CurrentPosition = position;
}