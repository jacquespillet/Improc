#pragma once
#include "CommonIncludes.hpp"
#include <QGraphicsView> 

#include "CurveEditorScene.h"

class CurveEditor : public QGraphicsView
{
    Q_OBJECT
public:
    CurveEditor(QWidget *parent = 0);


protected:
    virtual void wheelEvent(QWheelEvent *event) override;
    
    float ZoomFactor=1;
    CurveEditorScene *scene;
};
