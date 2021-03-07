#include "CurveEditor.h"
CurveEditor::CurveEditor(QWidget *parent) : QGraphicsView(parent)
{
    resize(800, 600);
    scale(1, -1);

    setDragMode(QGraphicsView::ScrollHandDrag);
    setInteractive(true);
    
    scene = new CurveEditorScene(this);
    setScene(scene);    
}

void CurveEditor::wheelEvent(QWheelEvent *event) 
{
    QPoint WindowCenter = QPoint(width() / 2, height()/2);
    QPointF CenterScene = mapToScene(WindowCenter); 

    QPoint MousePos = mapFromGlobal(QCursor::pos());
    QPointF MousePosSceneBefore = mapToScene(MousePos);

    ZoomFactor = 1 + event->angleDelta().y() * 0.001;

    scale(ZoomFactor, ZoomFactor);
    scene->SetScaleFactor(ZoomFactor);

    QPointF MousePosSceneAfter = mapToScene(MousePos);
    QPointF Difference = MousePosSceneAfter - MousePosSceneBefore;
    QPointF Delta = CenterScene - Difference;
    centerOn(Delta);
}