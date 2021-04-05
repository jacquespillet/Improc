#include "NodeEditor.h"

#include <QtWidgets/QGraphicsProxyWidget>
#include <QRect>
#include "NodeMenu.h"

NodeEditor::NodeEditor(QWidget *parent) : QGraphicsView(parent)
{
    resize(800, 600);
    scale(1, 1);

    setDragMode(QGraphicsView::ScrollHandDrag);
    setInteractive(true);
    
    scene = new NodeEditorScene(this);
    setScene(scene);    

	CreatingConnection = false;

    NodeMenu *menu = new NodeMenu(this);
    menu->show();

	TemporaryConnection = nullptr;
}

void NodeEditor::wheelEvent(QWheelEvent *event) 
{
    QPoint WindowCenter = QPoint(width() / 2, height()/2);
    QPointF CenterScene = mapToScene(WindowCenter); 

    QPoint MousePos = mapFromGlobal(QCursor::pos());
    QPointF MousePosSceneBefore = mapToScene(MousePos);

    ZoomFactor = 1 + event->angleDelta().y() * 0.001;

    scale(ZoomFactor, ZoomFactor);

    QPointF MousePosSceneAfter = mapToScene(MousePos);
    QPointF Difference = MousePosSceneAfter - MousePosSceneBefore;
    QPointF Delta = CenterScene - Difference;
    centerOn(Delta);
}

void NodeEditor::keyPressEvent(QKeyEvent *keyEvent)
{
    if(keyEvent->key() == Qt::Key_Delete)
    {
        QList<QGraphicsItem *> selectedItems = scene->selectedItems();
        
        std::vector<Node*> nodesToErase;
        std::vector<Connection*> connectionsToErase;

        for(int i=0; i<selectedItems.size(); i++)
        {
            Node *node=  dynamic_cast<Node*>(selectedItems[i]);
            if(node)
            {
                scene->removeItem(selectedItems[i]);
                nodesToErase.push_back(node);
                for(int j=0; j<node->inputConnections.size(); j++)
                {
                    scene->removeItem(node->inputConnections[j]);
                    connectionsToErase.push_back(node->inputConnections[j]);
                }
                
                for(int j=0; j<node->outputConnections.size(); j++)
                {
                    for(int k=0; k<node->outputConnections[j].size(); k++)
                    {
                        scene->removeItem(node->outputConnections[j][k]);
                        connectionsToErase.push_back(node->outputConnections[j][k]);
                    }
                }
            }

            Connection *connection=  dynamic_cast<Connection*>(selectedItems[i]);
            if(connection)
            {
                connectionsToErase.push_back(connection);
            }
        }

        for(int i=Nodes.size()-1; i>=0 ; i--)
        {
            for(int j=0; j<nodesToErase.size(); j++)
            {
                if(Nodes[i] == nodesToErase[j])
                {
                    delete Nodes[i];
                    Nodes.erase(Nodes.begin() + i);
                    nodesToErase.erase(nodesToErase.begin() + j);
                    break;
                }
            }
        }

        for(int i=Connections.size()-1; i>=0 ; i--)
        {
            for(int j=0; j<connectionsToErase.size(); j++)
            {
                if(Connections[i] == connectionsToErase[j])
                {
                    Connections[i]->StartNode->eraseOutputConnection(Connections[i]);
                    Connections[i]->EndNode->eraseInputConnection(Connections[i]);

                    delete Connections[i];
                    Connections.erase(Connections.begin() + i);
                    connectionsToErase.erase(connectionsToErase.begin() + j);
                    break;
                }
            }
        }
    }
    scene->update();
}


void NodeEditor::mousePressEvent(QMouseEvent *event)
{
    //Rubber band selection
    if(QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier))
    {
        setDragMode(QGraphicsView::RubberBandDrag);
    }
    else
    {
        setDragMode(QGraphicsView::ScrollHandDrag);
    }


    //Normal event
    QGraphicsView::mousePressEvent(event);

    clicked=true;
    QList<QGraphicsItem *> selectedItems = scene->selectedItems();

	selectionOffsets = std::vector<QPointF>(selectedItems.size());
    for(int i=0; i<selectedItems.size(); i++)
    {
        Node *node = dynamic_cast<Node*>(selectedItems[i]);
        if(node)
        {
            QPointF offset = mapToScene(event->pos()) - selectedItems[i]->scenePos();
            selectionOffsets[i] = offset;
        }
    }

    //Connection handling
    QPointF scenePosition = mapToScene(event->pos());
    for(int i=0; i<Nodes.size(); i++)
    {
        int8_t connection = Nodes[i]->CheckInputConnection(scenePosition);
        if(connection >= 0)
        {
            StartCreateConnection(Nodes[i], true, connection, scenePosition);
            break;
        }
        
        connection = Nodes[i]->CheckOutputConnection(scenePosition);
        if(connection >= 0)
        {
            StartCreateConnection(Nodes[i], false, connection, scenePosition);
            break;
        }
    }  
}

void NodeEditor::mouseReleaseEvent(QMouseEvent *event)
{    
    clicked=false;

    QGraphicsView::mouseReleaseEvent(event);
    
    if(CreatingConnection)
    {
        QGraphicsView::mouseReleaseEvent(event);

        QPointF scenePosition = mapToScene(event->pos());

        bool attached = false;
        for(int i=0; i<Nodes.size(); i++)
        {
            int8_t connection = Nodes[i]->CheckInputConnection(scenePosition);
            if(connection >= 0)
            {
                attached = EndCreateConnection(Nodes[i], true, connection, scenePosition);
            }
            
            connection = Nodes[i]->CheckOutputConnection(scenePosition);
            if(connection >= 0)
            {
                attached = EndCreateConnection(Nodes[i], false, connection, scenePosition);
            }
        }

        if(!attached)
        {
            scene->removeItem(TemporaryConnection);
            scene->update();
        }

        if(TemporaryConnection != nullptr) delete TemporaryConnection;

        CreatingConnection=false;
    }

}

//TODO : draw the connectoin path
void NodeEditor::mouseMoveEvent(QMouseEvent *event)
{
    if(clicked && !QApplication::keyboardModifiers().testFlag(Qt::ShiftModifier) && !CreatingConnection)
    {
        for(int i=0; i<scene->selectedItems().size(); i++)
        {
            Node *node = dynamic_cast<Node*>(scene->selectedItems()[i]);
            if(node)
            {
                scene->selectedItems()[i]->setPos(mapToScene(event->pos()) - selectionOffsets[i]);
            }
        }
        QGraphicsView::mouseMoveEvent(event);
    }
    else if(CreatingConnection)
    {
        if(TemporaryConnection != nullptr)
        {
            TemporaryConnection->SetCurrentPosition(mapToScene(event->pos()));
        }
    }
    else
    {
        QGraphicsView::mouseMoveEvent(event);
    }

    scene->update();

    
}






void NodeEditor::StartCreateConnection(Node *node, bool isInput, int index, QPointF scenePosition)
{
    node->clicked=false;
    CreatingConnection=true;

    TemporaryConnection = new Connection(node, isInput, index);
    TemporaryConnection->SetCurrentPosition(scenePosition);
    scene->addItem(TemporaryConnection);
    scene->update();   
}

bool NodeEditor::EndCreateConnection(Node *node, bool isInput, int index, QPointF scenePosition)
{
    if(TemporaryConnection->StartNode != nullptr && TemporaryConnection->StartNode == node) return false;
    if(TemporaryConnection->EndNode != nullptr && TemporaryConnection->EndNode == node) return false;

    bool success = TemporaryConnection->FinishConnection(node, isInput, index);
    if(!success) return false;

    CreatingConnection=false;
    
    Connections.push_back(TemporaryConnection);

    TemporaryConnection->EndNode->Compute();

    TemporaryConnection = nullptr;
    scene->update();   


    
    return true;
}
