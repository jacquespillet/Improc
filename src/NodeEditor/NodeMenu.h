#include <QtWidgets/QWidget>

class Node;
class NodeEditor;

class NodeMenu : public QWidget
{
Q_OBJECT
public:
    NodeMenu(NodeEditor *editor);

private:
    NodeEditor *editor;
    void AddNodeToScene(Node *node);
};