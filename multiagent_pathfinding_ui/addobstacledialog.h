#ifndef ADDOBSTACLEDIALOG_H
#define ADDOBSTACLEDIALOG_H

#include <QWidget>

namespace Ui {
class addObstacleDialog;
}

class addObstacleDialog : public QWidget
{
    Q_OBJECT

public:
    explicit addObstacleDialog(QWidget *parent = nullptr);
    ~addObstacleDialog();

private:
    Ui::addObstacleDialog *ui;
};

#endif // ADDOBSTACLEDIALOG_H
