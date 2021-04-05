#include "Node.h"
#include "Image/ImProcTypes.h"

class QLabel;

class ImageData : public NodeData
{
public:
    ImageData();
    ImProc::image Image;
    bool loaded=false;
    QString fileName;
};

class ImageNode : public Node
{
public :
    ImageNode(float X, float Y);
    virtual void Compute();
    
    virtual NodeData *GetValue();
};

class DisplayImageNode : public Node
{
public :
    DisplayImageNode(float X, float Y);
    virtual void Compute();

    QLabel *imageLabel;
    QPixmap pixmap;
};