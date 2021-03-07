#include "BaseProcessWidget.hpp"


SelectColorButtonWidget::SelectColorButtonWidget( QWidget* Parent, QColor Color )
{
    this->Color = Color;
    connect( this, SIGNAL(clicked()), this, SLOT(ChangeColor()) );
}

void SelectColorButtonWidget::UpdateColor()
{
    setStyleSheet( "background-color: " + Color.name() );
}

void SelectColorButtonWidget::ChangeColor()
{
    QColor NewColor = QColorDialog::getColor(Color,parentWidget());
    if ( NewColor != Color )
    {
        SetColor( NewColor );
    }
}

void SelectColorButtonWidget::SetColor( const QColor& Color )
{
    this->Color = Color;
    UpdateColor();

    emit Modified();
}

//

Vector4FEditor::Vector4FEditor(QWidget *Parent, QString widgetName, float _r,float _g,float _b,float _a) : QGroupBox(widgetName)
{
    this->r = _r;
    this->g = _g;
    this->b = _b;
    this->a = _a;

    setMinimumHeight(100);
    
    layout = new QGridLayout();

    QLabel *RLabel = new QLabel ("X");
    QLabel *GLabel = new QLabel ("Y");
    QLabel *BLabel = new QLabel ("Z");
    QLabel *ALabel = new QLabel ("W");
    layout->addWidget(RLabel, 0, 0, 1, 1);
    layout->addWidget(GLabel, 0, 1, 1, 1);
    layout->addWidget(BLabel, 0, 2, 1, 1);
    layout->addWidget(ALabel, 0, 3, 1, 1);


    QDoubleSpinBox *RSpinBox = new QDoubleSpinBox(this);
    RSpinBox->setValue(r);
    RSpinBox->setRange(-100.0, 100.0);
    RSpinBox->setSingleStep(0.05);
    layout->addWidget(RSpinBox, 1, 0, 1, 1);
    
    QDoubleSpinBox *GSpinBox = new QDoubleSpinBox(this);
    GSpinBox->setValue(g);
    GSpinBox->setRange(-100.0, 100.0);
    GSpinBox->setSingleStep(0.05);
    layout->addWidget(GSpinBox, 1, 1, 1, 1);
    
    QDoubleSpinBox *BSpinBox = new QDoubleSpinBox(this);
    BSpinBox->setValue(b);
    BSpinBox->setRange(-100.0, 100.0);
    BSpinBox->setSingleStep(0.05);
    layout->addWidget(BSpinBox, 1, 2, 1, 1);
    
    QDoubleSpinBox *ASpinBox = new QDoubleSpinBox(this);
    ASpinBox->setValue(a);
    ASpinBox->setRange(-100.0, 100.0);
    ASpinBox->setSingleStep(0.05);
    layout->addWidget(ASpinBox, 1, 3, 1, 1);

    connect(RSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double value){
        r = (float) value;
        emit Modified();
    });
    connect(GSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double value){
        g = (float) value;
        emit Modified();
    });
    connect(BSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double value){
        b = (float) value;
        emit Modified();
    });
    connect(ASpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double value){
        a = (float) value;
        emit Modified();
    });

    setLayout(layout);
}


//

BaseProcessWidget::BaseProcessWidget(QString ProcessName, SidePanel *parent, uint32_t Index) : QGroupBox(ProcessName)
{
    this->Index = Index;

    // setMaximumHeight(100);
    layout = new QVBoxLayout();
    QHBoxLayout *HeaderLayout = new QHBoxLayout();
    layout->addLayout(HeaderLayout);

    QPushButton *RemoveButton = new QPushButton("Remove");
    HeaderLayout->addWidget(RemoveButton);
    connect(RemoveButton, &QPushButton::pressed, this, [this](){
        emit Remove(this->Index);
    });
    
    setLayout( layout );
}