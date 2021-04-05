#pragma once

#include <QtWidgets/QGraphicsItem>
#include "Nodes/Node.h"

// class for customization
class Connection  :public QGraphicsItem
{
public:
    Connection();
    QRectF boundingRect() const;

    Connection(Node *node, bool isInput, int index);
    bool FinishConnection(Node *node, bool isInput, int index);

    void SetCurrentPosition(QPointF position);
    
    Node *StartNode;
    Node *EndNode;

    int StartIndex;
    int EndIndex;

    QPointF CurrentPosition;

    bool finished = false;

    bool selected=false;

    // overriding paint()
    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget);

    QPen nonSelectedPen;
    QPen selectedPen;
private:
    QRectF boundingBox;

};