#include "CurveEditorScene.h"
#include <QGraphicsTextItem> 
#include <QGraphicsSceneMouseEvent> 

CurveEditorScene::CurveEditorScene(QGraphicsView *View) : QGraphicsScene(-500, -500, 1000, 1000, View)
{
    QPen xAxisPen(Qt::red);
    xAxisPen.setWidth(0);
    xAxis = addLine(-500, 0, 500, 0, xAxisPen);

    QPen yAxisPen(Qt::green);
    yAxisPen.setWidth(0);
    yAxis = addLine(0, -500, 0, 500, yAxisPen);


    QPen MainLinesPen(QColor(200, 200, 200, 50));
    MainLinesPen.setWidth(0);
    for(int LineIndex=-500, Index=0; LineIndex<500; LineIndex+=10, Index++)
    {
        if(LineIndex==0) continue;

        QGraphicsLineItem *x = addLine(-1000, LineIndex, 1000, LineIndex, MainLinesPen);
        MainHorizontalLines.push_back(x);
        QGraphicsLineItem *y = addLine(LineIndex, -1000, LineIndex, 1000, MainLinesPen);
        MainVerticalLines.push_back(y);

		if(Index % 3 == 0)
		{
			QString LabelString = QString::number(LineIndex);
			QGraphicsTextItem *XLabel = addText(LabelString, QFont("Arial", 10));
			XLabel->setTransform(QTransform::fromScale(1, -1), false);
			XLabel->setPos(QPointF(0, LineIndex + 0.5 * XLabel->boundingRect().height()));
            MainHorizontalLabels.push_back(XLabel);

			QGraphicsTextItem *YLabel = addText(LabelString, QFont("Arial", 10));
			YLabel->setTransform(QTransform::fromScale(1, -1), false);
			QTransform transform;	
			transform.rotate(90);
			YLabel->setTransform(transform, true);
			YLabel->setPos(QPointF(LineIndex + 0.5 * XLabel->boundingRect().height(), 0));
            MainVerticalLabels.push_back(YLabel);
		}
    }


    Curve = new LinearCurve();
    addItem(Curve);

}

void CurveEditorScene::SetScaleFactor(float ScaleFactor)
{
    this->ScaleFactor = ScaleFactor;

    for(int i=0;i<MainVerticalLabels.size(); i++)
    {
        MainVerticalLabels[i]->setTransform(QTransform::fromScale(1/ScaleFactor, 1/ScaleFactor), true);
        MainHorizontalLabels[i]->setTransform(QTransform::fromScale(1/ScaleFactor, 1/ScaleFactor), true);
    }
}

void CurveEditorScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    ControlPoint *control = new ControlPoint(mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
    addItem(control);
    Curve->AddControlPoint(control);
}