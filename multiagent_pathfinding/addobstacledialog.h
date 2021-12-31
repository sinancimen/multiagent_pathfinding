#ifndef ADDOBSTACLEDIALOG_H
#define ADDOBSTACLEDIALOG_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>

class addObstacleDialog : public QWidget
{
    Q_OBJECT
public:
    explicit addObstacleDialog(QWidget *parent = nullptr);
private:
    QLineEdit *m_PositionXTextbox;
    QLineEdit *m_PositionYTextbox;
    QComboBox *m_ShapeSelectionComboBox;
    QLabel *m_PositionXLabel;
    QLabel *m_PositionYLabel;

signals:

};

#endif // ADDOBSTACLEDIALOG_H
