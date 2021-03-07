#include "ControlPoint.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

ControlPoint::ControlPoint(float X, float Y) : QGraphicsEllipseItem(QRectF(-4, -4, 8, 8))
{
    setPos(X, Y);

    BrushSelected = QBrush(Qt::red);
    BrushUnselected = QBrush(Qt::green);

    setBrush(BrushSelected);
}


void ControlPoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    clicked=true;
}

void ControlPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    clicked=false;
}

void ControlPoint::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    setPos(event->scenePos());
    ParentCurve->Refresh();
}



LinearCurve::LinearCurve()
{}

void LinearCurve::AddControlPoint(ControlPoint* Point)
{
    ControlPoints.push_back(Point);
    Point->ParentCurve = this;
    Refresh();
}

QRectF LinearCurve::boundingRect() const
{
    return BoundingRectangle;
}


//define the function:
bool comparator(const ControlPoint* lhs, const ControlPoint* rhs) {
    QPointF position = lhs->scenePos();
    QPointF otherPosition = rhs->scenePos();
    
    return position.x() < otherPosition.x();
}

void LinearCurve::Refresh()
{
    QPointF TopLeft(99999999, 99999999);
    QPointF BottomRight(-99999999, -99999999);
    for(int i=0; i<ControlPoints.size(); i++)
    {
        QPointF Position = ControlPoints[i]->scenePos();
        if(Position.x() < TopLeft.x()) TopLeft.setX(Position.x());
        if(Position.y() < TopLeft.y()) TopLeft.setY(Position.y());
        
        if(Position.x() > BottomRight.x()) BottomRight.setX(Position.x());
        if(Position.y() > BottomRight.y()) BottomRight.setY(Position.y());
    }
    BoundingRectangle = QRectF(TopLeft, BottomRight);

    std::sort(ControlPoints.begin(), ControlPoints.end(), comparator);
    scene()->update();
}

void LinearCurve::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(ControlPoints.size() >= 2)
    {        
        QPainterPath path;
        path.moveTo(ControlPoints[0]->scenePos());
        for(int i=1; i<ControlPoints.size(); i++)
        {
            path.lineTo(ControlPoints[i]->scenePos());
        }

        painter->drawPath(path);
    }
}



float LinearCurve::SampleAt(float Time)
{
    bool Found=false;
    u32 FirstIndex, SecondIndex;

    float StartTime = ControlPoints[0]->scenePos().x();
    float EndTime = ControlPoints[ControlPoints.size()-1]->scenePos().x();
    if(Time < StartTime || Time > EndTime) return 0.0f;


    u32 CurrentIndex=0;
    while(!Found && CurrentIndex < ControlPoints.size())
    {
        float First = ControlPoints[CurrentIndex]->scenePos().x();
        float Second = ControlPoints[CurrentIndex+1]->scenePos().x();
        
        if(First < Time && Second > Time) 
        {
            Found = true;
            FirstIndex = CurrentIndex;
            SecondIndex = CurrentIndex+1;
            break;
        }

        CurrentIndex++;
    }

    float FirstTime = ControlPoints[FirstIndex]->scenePos().x();
    float SecondTime = ControlPoints[SecondIndex]->scenePos().x();

    float FirstValue = ControlPoints[FirstIndex]->scenePos().y();
    float SecondValue = ControlPoints[SecondIndex]->scenePos().y();

    float T = (Time - FirstTime) / (SecondTime - FirstTime);
    float Result = (1.0f - T) * FirstValue + T * SecondValue;
    
    return Result;
}

std::vector<float> LinearCurve::Export(float Start, float End, float Delta)
{
    int TotalSize = (End - Start) / Delta;
    float CurrentTime = Start;

    std::vector<float> Result(TotalSize);
    
    float StartTime = ControlPoints[0]->scenePos().x();
    float EndTime = ControlPoints[ControlPoints.size()-1]->scenePos().x();

    uint32_t CurrentIndex = 0;

    for(int i=0; i<TotalSize; i++)
    {

        if(CurrentTime < StartTime || CurrentTime > EndTime)
        {
            Result.push_back(0);
        }
        else
        {
            float First = ControlPoints[CurrentIndex]->scenePos().x();
            float Second = ControlPoints[CurrentIndex+1]->scenePos().x();

            while(!(First < CurrentTime && Second > CurrentTime))
            {
                CurrentIndex++;
            }
        
            float FirstTime = ControlPoints[CurrentIndex]->scenePos().x();
            float SecondTime = ControlPoints[CurrentIndex+1]->scenePos().x();

            float FirstValue = ControlPoints[CurrentIndex]->scenePos().y();
            float SecondValue = ControlPoints[CurrentIndex+1]->scenePos().y();

            float T = (CurrentTime - FirstTime) / (SecondTime - FirstTime);
            float Value = (1.0f - T) * FirstValue + T * SecondValue;
            
            Result.push_back(Value);
        }


        CurrentTime  += Delta; 
    }

    return Result;
}
