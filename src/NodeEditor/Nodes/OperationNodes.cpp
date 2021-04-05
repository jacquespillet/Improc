#include "OperationNodes.hpp"
#include "../Connection.h"
#include "BaseNodes.hpp"
//

AddNode::AddNode(float X, float Y) : Node(2, 1, "Add")
{
    value=nullptr;
    setPos(X, Y);
}

void AddNode::Compute() 
{
    if(inputConnections[0] == nullptr || inputConnections[1] == nullptr) return;

    //Add the actual nodes
    Node *FirstNode = inputConnections[0]->StartNode;
    Node *SecondNode = inputConnections[1]->StartNode;

    NumberData *firstNumberValue = dynamic_cast<NumberData*>(FirstNode->GetValue());
    NumberData *secondNumberValue = dynamic_cast<NumberData*>(SecondNode->GetValue());
    if(firstNumberValue && secondNumberValue)
    {
        float firstValue = firstNumberValue->value; 
        float secondValue = secondNumberValue->value;

        if(value != nullptr) delete value;
        value =  new NumberData(firstValue + secondValue);

        ComputeNext();

        return;
    }
    
    // StringNode* FirstNodeString = dynamic_cast<StringNode*>(FirstNode); 
    // StringNode* SecondNodeString = dynamic_cast<StringNode*>(SecondNode); 
    // if(FirstNodeString && SecondNodeString)
    // {
    //     stringValue = FirstNodeString->GetValue() + SecondNodeString->GetValue();

    //     for(int i=0; i<outputConnections[0].size(); i++)
    //     {
    //         outputConnections[0][i]->EndNode->Compute();
    //     }

    //     return;
    // }

}

NodeData * AddNode::GetValue()
{
    return value;
}

///

SubtractNode::SubtractNode(float X, float Y) : Node(2, 1, "Subtract")
{
    value=nullptr;
    setPos(X, Y);
}

void SubtractNode::Compute() 
{
    if(inputConnections[0] == nullptr || inputConnections[1] == nullptr) return;

    //Subtract the actual nodes
    Node *FirstNode = inputConnections[0]->StartNode;
    Node *SecondNode = inputConnections[1]->StartNode;

    NumberData *firstNumberValue = dynamic_cast<NumberData*>(FirstNode->GetValue());
    NumberData *secondNumberValue = dynamic_cast<NumberData*>(SecondNode->GetValue());
    if(firstNumberValue && secondNumberValue)
    {
        float firstValue = firstNumberValue->value; 
        float secondValue = secondNumberValue->value;

        if(value != nullptr) delete value;
        value =  new NumberData(firstValue - secondValue);

        ComputeNext();

        return;
    }
    
    // StringNode* FirstNodeString = dynamic_cast<StringNode*>(FirstNode); 
    // StringNode* SecondNodeString = dynamic_cast<StringNode*>(SecondNode); 
    // if(FirstNodeString && SecondNodeString)
    // {
    //     stringValue = FirstNodeString->GetValue() + SecondNodeString->GetValue();

    //     for(int i=0; i<outputConnections[0].size(); i++)
    //     {
    //         outputConnections[0][i]->EndNode->Compute();
    //     }

    //     return;
    // }

}

NodeData * SubtractNode::GetValue()
{
    return value;
}

///

MultiplyNode::MultiplyNode(float X, float Y) : Node(2, 1, "Multiply")
{
    value=nullptr;
    setPos(X, Y);
}

void MultiplyNode::Compute() 
{
    if(inputConnections[0] == nullptr || inputConnections[1] == nullptr) return;

    //Multiply the actual nodes
    Node *FirstNode = inputConnections[0]->StartNode;
    Node *SecondNode = inputConnections[1]->StartNode;

    NumberData *firstNumberValue = dynamic_cast<NumberData*>(FirstNode->GetValue());
    NumberData *secondNumberValue = dynamic_cast<NumberData*>(SecondNode->GetValue());
    if(firstNumberValue && secondNumberValue)
    {
        float firstValue = firstNumberValue->value; 
        float secondValue = secondNumberValue->value;

        if(value != nullptr) delete value;
        value =  new NumberData(firstValue * secondValue);

        ComputeNext();

        return;
    }
    
    // StringNode* FirstNodeString = dynamic_cast<StringNode*>(FirstNode); 
    // StringNode* SecondNodeString = dynamic_cast<StringNode*>(SecondNode); 
    // if(FirstNodeString && SecondNodeString)
    // {
    //     stringValue = FirstNodeString->GetValue() + SecondNodeString->GetValue();

    //     for(int i=0; i<outputConnections[0].size(); i++)
    //     {
    //         outputConnections[0][i]->EndNode->Compute();
    //     }

    //     return;
    // }

}

NodeData * MultiplyNode::GetValue()
{
    return value;
}

///

DivideNode::DivideNode(float X, float Y) : Node(2, 1, "Divide")
{
    value=nullptr;
    setPos(X, Y);
}

void DivideNode::Compute() 
{
    if(inputConnections[0] == nullptr || inputConnections[1] == nullptr) return;

    //Divide the actual nodes
    Node *FirstNode = inputConnections[0]->StartNode;
    Node *SecondNode = inputConnections[1]->StartNode;

    NumberData *firstNumberValue = dynamic_cast<NumberData*>(FirstNode->GetValue());
    NumberData *secondNumberValue = dynamic_cast<NumberData*>(SecondNode->GetValue());
    if(firstNumberValue && secondNumberValue)
    {
        float firstValue = firstNumberValue->value; 
        float secondValue = secondNumberValue->value;

        if(value != nullptr) delete value;
        value =  new NumberData(firstValue / secondValue);

        ComputeNext();

        return;
    }
    
    // StringNode* FirstNodeString = dynamic_cast<StringNode*>(FirstNode); 
    // StringNode* SecondNodeString = dynamic_cast<StringNode*>(SecondNode); 
    // if(FirstNodeString && SecondNodeString)
    // {
    //     stringValue = FirstNodeString->GetValue() + SecondNodeString->GetValue();

    //     for(int i=0; i<outputConnections[0].size(); i++)
    //     {
    //         outputConnections[0][i]->EndNode->Compute();
    //     }

    //     return;
    // }

}

NodeData * DivideNode::GetValue()
{
    return value;
}