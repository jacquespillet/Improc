#include "Node.h"

class NumberData : public NodeData
{
public:
    NumberData(float value) : value(value){}
    float value;
};

class NumberNode : public Node
{
public :
    NumberNode(float X, float Y);
    virtual void Compute();
    
    virtual NodeData *GetValue();
};

//

class StringData : public NodeData
{
public:
    StringData(QString value) : value(value){}
    QString value;
};

class FileNode : public Node
{
public :
    FileNode(float X, float Y);
    virtual void Compute();
    
    virtual NodeData *GetValue();
};

//

class DisplayNode : public Node
{
public :
    DisplayNode(float X, float Y);
    virtual void Compute();
private:
    QTextEdit *textEdit;
};

