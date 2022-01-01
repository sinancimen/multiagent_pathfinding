#ifndef ADDOBSTACLEDIALOG_H
#define ADDOBSTACLEDIALOG_H

#include <QWidget>
#include <QStackedWidget>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>

class addObstacleDialog : public QStackedWidget
{
    Q_OBJECT
public:
    explicit addObstacleDialog(QStackedWidget *parent = nullptr);
private:
    QLineEdit *m_PositionXTextbox;
    QLineEdit *m_PositionYTextbox;
    QComboBox *m_ShapeSelectionComboBox;
    QLabel *m_PositionXLabel;
    QLabel *m_PositionYLabel;
    QWidget *m_CircularWidget;
    QWidget *m_RectangularWidget;

signals:

};

#endif // ADDOBSTACLEDIALOG_H
