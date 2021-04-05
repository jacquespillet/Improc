#pragma once
#include "CommonIncludes.hpp"
#include <QGraphicsView> 

#include "Nodes/Node.h"

class NodeEditorScene : public QGraphicsScene
{
    Q_OBJECT
    QGraphicsLineItem *xAxis;
    QGraphicsLineItem *yAxis;
public:
    NodeEditorScene(QGraphicsView *View);

};
