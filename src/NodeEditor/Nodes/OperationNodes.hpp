#include "Node.h"

class AddNode : public Node
{
public :
    AddNode(float X, float Y);
    virtual void Compute();

    virtual NodeData *GetValue();
};

class SubtractNode : public Node
{
public :
    SubtractNode(float X, float Y);
    virtual void Compute();

    virtual NodeData *GetValue();
};

class MultiplyNode : public Node
{
public :
    MultiplyNode(float X, float Y);
    virtual void Compute();

    virtual NodeData *GetValue();
};

class DivideNode : public Node
{
public :
    DivideNode(float X, float Y);
    virtual void Compute();

    virtual NodeData *GetValue();
};