#include "NodeEditorScene.h"

#include "Nodes/Node.h"

NodeEditorScene::NodeEditorScene(QGraphicsView *View) : QGraphicsScene(-50000, -50000, 100000, 100000, View)
{
    QPen xAxisPen(Qt::red);
    xAxisPen.setWidth(0);
    xAxis = addLine(-500, 0, 500, 0, xAxisPen);

    QPen yAxisPen(Qt::green);
    yAxisPen.setWidth(0);
    yAxis = addLine(0, -500, 0, 500, yAxisPen);
}

