#include "addrobotdialog.h"

addRobotDialog::addRobotDialog(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(250, 300);
    m_PositionXTextbox = new QLineEdit(this);
    m_PositionXTextbox->setGeometry(150,10,90,30);
    m_PositionXLabel = new QLabel(this);
    m_PositionXLabel->setGeometry(10,10,130,30);
    m_PositionXLabel->setText("X Position");
    m_PositionYTextbox = new QLineEdit(this);
    m_PositionYTextbox->setGeometry(150,45,90,30);
    m_PositionYLabel = new QLabel(this);
    m_PositionYLabel->setGeometry(10,45,130,30);
    m_PositionYLabel->setText("Y Position");
    m_GoalXTextbox = new QLineEdit(this);
    m_GoalXTextbox->setGeometry(150,80,90,30);
    m_GoalXLabel = new QLabel(this);
    m_GoalXLabel->setGeometry(10,80,130,30);
    m_GoalXLabel->setText("X Goal");
    m_GoalYTextbox = new QLineEdit(this);
    m_GoalYTextbox->setGeometry(150,115,90,30);
    m_GoalYLabel = new QLabel(this);
    m_GoalYLabel->setGeometry(10,115,130,30);
    m_GoalYLabel->setText("Y Goal");
    m_CommRangeTextbox = new QLineEdit(this);
    m_CommRangeTextbox->setGeometry(150,150,90,30);
    m_CommRangeLabel = new QLabel(this);
    m_CommRangeLabel->setGeometry(10,150,130,30);
    m_CommRangeLabel->setText("Communication Range");
    m_DetRangeTextbox = new QLineEdit(this);
    m_DetRangeTextbox->setGeometry(150,185,90,30);
    m_DetRangeLabel = new QLabel(this);
    m_DetRangeLabel->setGeometry(10,185,130,30);
    m_DetRangeLabel->setText("Detection Range");
    m_AddButton = new QPushButton(this);
    m_AddButton->setGeometry(90, 230, 70, 30);
    m_AddButton->setText("Add");
}
