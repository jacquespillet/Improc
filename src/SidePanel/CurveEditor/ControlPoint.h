#pragma once
#include "CommonIncludes.hpp"
#include <QGraphicsEllipseItem> 

class LinearCurve;

class ControlPoint : public QGraphicsEllipseItem
{
public:
    ControlPoint(float X, float Y);
	QBrush BrushSelected;
	QBrush BrushUnselected;
    LinearCurve *ParentCurve;

protected:
    
    bool clicked=false;

    virtual void 	mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void 	mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void 	mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#include <QPainter>
#include <QGraphicsItem>

// class for customization
class LinearCurve :public QGraphicsItem
{
public:
    LinearCurve();

    QRectF boundingRect() const;

    // overriding paint()
    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget);
               
    void AddControlPoint(ControlPoint* Point);

    void Refresh();

    float SampleAt(float Time);
    std::vector<float> Export(float Start, float End, float Delta);
private:
    std::vector<ControlPoint*> ControlPoints;
    QRectF BoundingRectangle;
};