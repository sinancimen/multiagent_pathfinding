#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpers.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view = ui->graphicsView;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(20,10, 980, 480);
    ui->graphicsView->setScene(scene);

    for (int i = 0; i < 30 ; i++)
    {
        brushes.push_back(QBrush(Qt::green));
        brushes.push_back(QBrush(Qt::red));
        brushes.push_back(QBrush(Qt::yellow));
        brushes.push_back(QBrush(Qt::magenta));
        brushes.push_back(QBrush(Qt::cyan));
        brushes.push_back(QBrush(Qt::darkGreen));
        brushes.push_back(QBrush(Qt::darkYellow));
    }
   

    Map = new map(50, 25);
    timer1 = new QTimer(this);
    connect(timer1, SIGNAL(timeout()), this, SLOT(timerEvent()));
    timer1->setInterval(200);
    timer1->start();
    timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(montecarloTimerEvent()));
    timer2->setInterval(700);
    timer2->start();
}

MainWindow::~MainWindow()
{
    //killTimer(timerId);
    delete ui;
}

void MainWindow::addToObstacleList()
{
    int posx = getPositionX_obs().toInt();
    int posy = getPositionY_obs().toInt();
    int length = getLength_obs().toInt();
    int width = getWidth_obs().toInt();
    int diameter = getDiameter_obs().toInt();
    int type = getObstacleType();
    obstacle* Obstacle = new obstacle(1, type, posx, posy, length, width, diameter);
    obstacleList.append(Obstacle);
    std::vector<int> position = Obstacle->getPosition();
    std::set<tile*> neighbours;
    if (type == 0)
    {
        QGraphicsRectItem* rectangle = new QGraphicsRectItem(position.at(0) * 20 + 10, position.at(1) * 20, Obstacle->getWidth() * 20, Obstacle->getLength() * 20);
        Obstacle->setGraphicalItem_rect(rectangle);
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < length; j++)
            {
                tile* temp_tile = findTileAtPosition(posx + i, posy + j);
                neighbours = Map->getGraph().out_neighbors(temp_tile);
                for (tile* adj_tile : neighbours)
                {
                    Map->graph.remove_edge(adj_tile, temp_tile);

                }
                neighbours.clear();
            }
        }
    }
    else
    {
        QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(position.at(0) * 20 + 10, position.at(1) * 20, Obstacle->getDiameter() * 20, Obstacle->getDiameter() * 20);
        Obstacle->setGraphicalItem_circle(circle);
        for (int i = -std::ceil(diameter/2); i < std::ceil(diameter/2); i++)
        {
            for (int j = -std::ceil(diameter / 2); j < std::ceil(diameter / 2); j++)
            {
                tile* temp_tile = findTileAtPosition(posx + i, posy + j);
                neighbours = Map->getGraph().out_neighbors(temp_tile);
                for (tile* adj_tile : neighbours)
                {
                    Map->graph.remove_edge(adj_tile, temp_tile);

                }
                neighbours.clear();
            }
        }
    }
    updateObstacleGraphics();
}

void MainWindow::addRobotToList()
{
    int identity;
    if (robotList.size() > 0)
    {
        identity = robotList.at(robotList.size() - 1)->getID() + 1;
    }
    else
    {
        identity = 0;
    }
    robot* Robot = new robot(identity, getCommRange().toInt(), getDetRange().toInt(), getGoalX().toInt(), getGoalY().toInt());
    Robot->setPosition(getPositionX().toInt(), getPositionY().toInt());
    QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(getPositionX().toInt()+10, getPositionY().toInt(), robot_diameter, robot_diameter);
    circle->setBrush(brushes.at(identity));
    circle->setOpacity(1.0);
    Robot->setGraphicObject(circle);
    QGraphicsEllipseItem* circle_goal = new QGraphicsEllipseItem(getGoalX().toInt() + 10, getGoalY().toInt(), robot_diameter, robot_diameter);
    circle_goal->setBrush(brushes.at(identity));
    circle_goal->setOpacity(0.25);
    Robot->setGraphicObject_goal(circle_goal);
    std::vector<tile*> tileList = Map->getTileList();
    for (unsigned int i = 0; i < tileList.size(); i++)
    {
        if ((tileList.at(i)->x_pos == Robot->getPosition().at(0)) && (tileList.at(i)->y_pos == Robot->getPosition().at(1)))
        {
            Robot->setTile(tileList.at(i));
            break;
        }
    }
    robotList.append(Robot);
    updateRobotGraphics();
}

void MainWindow::timerEvent()
{
    if (startStatus)
    {
        if (selected_method == 0)
        {
            timeLRA += 1;
        }
        else if (selected_method == 2)
        {
            timeWhcaSim++;
        }

        std::vector<robot*> movingRobots;
        if (selected_method != 2)
        {
            for (int i = 0; i < robotList.size(); i++)
            {
                if ((robotList.at(i)->getGoal().at(0) != robotList.at(i)->getPosition().at(0)) || (robotList.at(i)->getGoal().at(1) != robotList.at(i)->getPosition().at(1)))
                {
                    if (robotList.at(i)->getNextStep() != NULL)
                    {
                        movingRobots.push_back(robotList.at(i));
                    }
                }
            }
        }
        else
        {
            timeWhca++;
            if (timeWhca > window / 2)
            {
                timeWhca = 0;
                whcAStar_doOrdering();
                reservationTable.clear();
                for (int i = 0; i < robotList.size(); i++)
                {
                    whcAStar_Solver(robotList.at(i));
                }
            }
            for (int i = 0; i < robotList.size(); i++)
            {
                movingRobots.push_back(robotList.at(i));
            }
        }
        

        if (selected_method == 0)
        {
            pathLRA += movingRobots.size();
        }

        for (unsigned int i = 0; i < movingRobots.size(); i++)
        {
            robot* robot_to_move = movingRobots.at(i);
            tile* next_tile = robot_to_move->getNextStep();
            bool collision = false;

            if (selected_method == 0)
            {
                for (int j = 0; j < robotList.size(); j++)
                {
                    if (robotList.at(j)->getNextStep() == next_tile && (robotList.at(j)->getPosition() != robot_to_move->getPosition()))
                    {
                        collision = true;
                    }
                }

                if (collision)
                {
                    map* MapClone = new map(Map);
                    MapClone->graph.remove_edge(robot_to_move->getTile(), next_tile);
                    localRepairAStar_Search(robot_to_move, MapClone);
                }
                else
                {
                    robot_to_move->takeStep();
                    updateRobotGraphics();
                }
            }

            else if (selected_method == 1)
            {
                robot_to_move->takeStep();
                updateRobotGraphics();
            }

            else if (selected_method == 2)
            {
                robot_to_move->takeStep();
                updateRobotGraphics();
                bool finish = checkForStatus();
                if (finish)
                {
                    startStatus = false;
                }
            }
            
        }

        if (movingRobots.size() == 0 )
        {
            startStatus = false;
            if (montecarloStatus)
            {
                sumOfAveragePath += averagePath;
                sumOfTimeOverSims += timeTaken;
                sumOfPath = 0;
            }
        }

        if (montecarloStatus && selected_method == 0 && timeLRA > 2 * getNumberOfSteps().toInt())
        {
            failure = true;
            startStatus = false;
        }
    }
        
}

tile* MainWindow::findTileAtPosition(int x, int y)
{
    tile* Tile;
    std::vector<tile*> tileList = Map->getTileList();
    for (unsigned int i = 0; i < tileList.size(); i++)
    {
        if ((tileList.at(i)->x_pos == x) && (tileList.at(i)->y_pos == y))
        {
            Tile = tileList.at(i);
            break;
        }
    }
    return Tile;
}

void MainWindow::setTimeTextbox(QString text)
{
    ui->totalTimeTextbox->setText(text);
}

void MainWindow::setPathTextbox(QString text)
{
    ui->totalPathTextbox->setText(text);
}

void MainWindow::setFailureTextbox(QString text)
{
    ui->failureTextbox->setText(text);
}
