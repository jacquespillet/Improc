#pragma once

#include <QtWidgets/QGraphicsItem>
#include <QPainter>
#include <QMouseEvent>
#include <QtWidgets/QTextEdit>

#define NODE_WIDTH 100
#define HEADER_SIZE 30

#define CONNECTION_SIZE 10
#define CONNECTION_SPACING 10

class NodeEditor;
class Connection;
class QGraphicsProxyWidget;
class QVBoxLayout;

class NodeData
{
public:
    virtual ~NodeData(){}
};


// class for customization
class Node  :public QGraphicsItem
{
public:
    Node(uint8_t inputs, uint8_t outputs, QString Name);
    ~Node();

    QRectF boundingRect() const;

    // overriding paint()
    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget);

    void DrawNode(QPainter *painter);
    void DrawInputs(QPainter *painter);
    void DrawOutputs(QPainter *painter);
    
    QString name;
    uint8_t inputs  = 0; 
    uint8_t outputs = 0;

    NodeEditor *editor;

    int8_t CheckInputConnection(QPointF position);
    int8_t CheckOutputConnection(QPointF position);

    QPointF GetInputPosition(uint8_t inputIndex);
    QPointF GetOutputPosition(uint8_t outputIndex);

    QPointF GetInputPositionScene(uint8_t inputIndex);
    QPointF GetOutputPositionScene(uint8_t outputIndex);

    void eraseInputConnection(Connection *connection);
    void eraseOutputConnection(Connection *connection);

    bool clicked=false;

    std::vector<Connection *> inputConnections;
    std::vector<std::vector<Connection*>> outputConnections;

    QGraphicsProxyWidget *proxy;

    virtual void Compute();

    virtual NodeData *GetValue();

protected:
    QPointF clickedPos;
        
    virtual void 	mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void 	mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void 	mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    
    void ComputeInputOutputPositions();

    void SetWidget(QWidget *widget);
    void AddWidget(QWidget *widget);

    float width, height;

    QRectF BoundingRectangle;
    QBrush nodeBrush;
    QBrush nodeSelectedBrush;
    QBrush textBrush;
    QBrush inputOutputBrush;

    std::vector <QPointF> outputPositions;
    std::vector <QPointF> inputPositions;

    void ComputeNext();
    
protected:
    NodeData *value;

    QVBoxLayout *layout;
    QWidget *mainWidget=nullptr;
};

