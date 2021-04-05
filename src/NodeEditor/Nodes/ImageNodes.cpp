#include "ImageNodes.hpp"
#include "BaseNodes.hpp"
#include "../Connection.h"
#include "Image/Processes/LoadImageProcess.h"

#include <QtWidgets/QLabel>


ImageData::ImageData()
{
    Image = {};
    loaded=false;
}

ImageNode::ImageNode(float X, float Y) : Node(1, 1, "Image")
{
    setPos(X, Y);
    value = new ImageData();
}

void ImageNode::Compute() 
{
    if(inputConnections[0] == nullptr ) return;

    Node *inputNode = inputConnections[0]->StartNode;
    
    StringData *fileNameData = dynamic_cast<StringData*>(inputNode->GetValue());
    if(fileNameData)
    {
        QString fileNameString = fileNameData->value; 
        if(fileNameString.size() == 0)
        {
            return;
        }
        
        ImageData *imageData = (ImageData*)value;
        if(imageData->loaded) {
            if(imageData->fileName.compare(fileNameString)==0){
                return;
            }
        }
        else
        {
            delete this->value;
            this->value = new ImageData();
            
            ImageData *imageData = (ImageData*)value;
            
            std::string tmpString = fileNameString.toStdString();
            const char* FileName = tmpString.c_str();
            imageData->Image = ImProc::ImageFromFile(FileName);
            
            ComputeNext();
        }
    }
}


NodeData * ImageNode::GetValue()
{
    return dynamic_cast<ImageData*>(value);
}

//

DisplayImageNode::DisplayImageNode(float X, float Y) : Node(1, 0, "Display Image")
{
    setPos(X, Y);
    imageLabel = new QLabel();
    QPixmap pixmap(300, 300);      
    pixmap.fill(Qt::white);
    imageLabel->setPixmap(pixmap);
    SetWidget(imageLabel);
}

void DisplayImageNode::Compute()
{
	if (inputConnections[0] == nullptr)
	{
		QPixmap pixmap;
		imageLabel->setPixmap(pixmap);
		return;
	}

    Node *inputNode = inputConnections[0]->StartNode;
    
    ImageData *imageData = dynamic_cast<ImageData*>(inputNode->GetValue());
    if(imageData)
    {
        uint32_t imageWidth = imageData->Image.Width;
        uint32_t imageHeight = imageData->Image.Height;

        QImage image(imageWidth, imageHeight, QImage::Format_RGBA8888);
        memcpy(image.bits(), imageData->Image.Data, imageHeight * imageWidth * 4);
        QPixmap pixmap = QPixmap::fromImage(image);
        
		pixmap = pixmap.scaledToWidth(300, Qt::FastTransformation);
		pixmap = pixmap.scaledToHeight(300, Qt::FastTransformation);
        
		imageLabel->setPixmap(pixmap);
    }
	else
	{
		QPixmap pixmap;
		imageLabel->setPixmap(pixmap);
		return;
	}

    ComputeInputOutputPositions();
}