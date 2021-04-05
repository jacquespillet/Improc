#pragma once
#include "CommonIncludes.hpp"
#include <QGraphicsView> 

#include "NodeEditorScene.h"
#include "Connection.h"

class NodeEditor : public QGraphicsView
{
Q_OBJECT
public:
    NodeEditor(QWidget *parent = 0);

    void StartCreateConnection(Node *node, bool isInput, int index, QPointF scenePosition);
    bool EndCreateConnection(Node *node, bool isInput, int index, QPointF scenePosition);

    NodeEditorScene *scene;
    std::vector<Node *> Nodes;

protected:
    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *keyEvent);
    
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;


    std::vector<Connection *> Connections;
    Connection *TemporaryConnection;
    
    QPointF clickedPos;
    std::vector<QPointF> selectionOffsets;

    float ZoomFactor=1;

    bool clicked=false;
    bool CreatingConnection=false;
    
    Node *ConnectionInputNode;
    Node *ConnectionOutputNode;
};
