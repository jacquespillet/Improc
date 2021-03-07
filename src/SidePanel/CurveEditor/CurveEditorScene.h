#pragma once
#include "CommonIncludes.hpp"
#include <QGraphicsView> 
#include "ControlPoint.h"


class CurveEditorScene : public QGraphicsScene
{
    Q_OBJECT
    QGraphicsLineItem *xAxis;
    QGraphicsLineItem *yAxis;

    std::vector<QGraphicsLineItem *> MainVerticalLines;
    std::vector<QGraphicsLineItem *> MainHorizontalLines;
    
    std::vector<QGraphicsTextItem *> MainVerticalLabels;
    std::vector<QGraphicsTextItem *> MainHorizontalLabels;

    LinearCurve *Curve;
public:
    CurveEditorScene(QGraphicsView *View);

    void SetScaleFactor(float ScaleFactor);
    float ScaleFactor;

protected:
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
};
