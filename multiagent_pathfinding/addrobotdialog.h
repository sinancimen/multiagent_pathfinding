#ifndef ADDROBOTDIALOG_H
#define ADDROBOTDIALOG_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

class addRobotDialog : public QWidget
{
    Q_OBJECT
public:
    explicit addRobotDialog(QWidget *parent = nullptr);

private:
    QLineEdit *m_PositionXTextbox;
    QLineEdit *m_PositionYTextbox;
    QLineEdit *m_GoalXTextbox;
    QLineEdit *m_GoalYTextbox;
    QLineEdit *m_CommRangeTextbox;
    QLineEdit *m_DetRangeTextbox;
    QLabel *m_PositionYLabel;
    QLabel *m_PositionXLabel;
    QLabel *m_GoalXLabel;
    QLabel *m_GoalYLabel;
    QLabel *m_CommRangeLabel;
    QLabel *m_DetRangeLabel;
    QPushButton *m_AddButton;
signals:

};

#endif // ADDROBOTDIALOG_H
