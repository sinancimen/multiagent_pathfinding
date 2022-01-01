#include "addobstacledialog.h"

addObstacleDialog::addObstacleDialog(QStackedWidget *parent)
    : QStackedWidget{parent}
{
    m_ShapeSelectionComboBox = new QComboBox(this);
    m_ShapeSelectionComboBox->addItem(tr("Rectangular"));
    m_ShapeSelectionComboBox->addItem(tr("Circular"));
    m_ShapeSelectionComboBox->setGeometry(50,10,150,30);
    //connect(m_ShapeSelectionComboBox, QOverload<int>::of(&QComboBox::activated), this, &QStackedWidget::setCurrentIndex);

    m_CircularWidget = new QWidget();
    m_RectangularWidget = new QWidget();
    m_CircularWidget->setFixedSize(250,300);
    m_RectangularWidget->setFixedSize(250,300);

    m_PositionXTextbox = new QLineEdit(m_CircularWidget);
    m_PositionXTextbox->setGeometry(150,45,90,30);
    m_PositionXLabel = new QLabel(m_CircularWidget);
    m_PositionXLabel->setGeometry(10,45,130,30);
    m_PositionXLabel->setText("X Position");
    m_PositionYTextbox = new QLineEdit(m_CircularWidget);
    m_PositionYTextbox->setGeometry(150,80,90,30);
    m_PositionYLabel = new QLabel(m_CircularWidget);
    m_PositionYLabel->setGeometry(10,80,130,30);
    m_PositionYLabel->setText("Y Position");

    m_PositionXTextbox = new QLineEdit(m_RectangularWidget);
    m_PositionXTextbox->setGeometry(150,45,90,30);
    m_PositionXLabel = new QLabel(m_RectangularWidget);
    m_PositionXLabel->setGeometry(10,45,130,30);
    m_PositionXLabel->setText("X Position");
    m_PositionYTextbox = new QLineEdit(m_RectangularWidget);
    m_PositionYTextbox->setGeometry(150,80,90,30);
    m_PositionYLabel = new QLabel(m_RectangularWidget);
    m_PositionYLabel->setGeometry(10,80,130,30);
    m_PositionYLabel->setText("Y Position");


    this->addWidget(m_CircularWidget);
    this->addWidget(m_RectangularWidget);

}
