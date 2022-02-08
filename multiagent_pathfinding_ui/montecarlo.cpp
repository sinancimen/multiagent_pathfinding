#include "mainwindow.h"
#include <random>
#include <iterator>

void MainWindow::monteCarloClicked()
{
	int num_of_robots = getNumberOfRobots().toInt();
	int num_of_steps = getNumberOfSteps().toInt();
	int num_of_simulations = getNumberOfSimulations().toInt();
	this->sumOfPath = 0;
	this->timeTaken = 0;
	this->noOfFailures = 0;
	this->averagePath = 0.0;
	this->sumOfTimeOverSims = 0;
	this->sumOfAveragePath = 0.0;
	this->totalTimeLRA = 0;
	this->totalPathLRA = 0;
	montecarlo_list = generateRandomRobots(num_of_robots, num_of_steps, num_of_simulations);
	montecarloStatus = true;
}

std::vector<QList<robot*>> MainWindow::generateRandomRobots(int num_robot, int num_steps, int num_simulations)
{
	std::vector<QList<robot*>> randomRobots;
	QList<robot*> tempList;
	for (int i = 0; i < num_simulations; i++)
	{
		tempList.clear();
		for (int j = 0; j < num_robot; j++)
		{
			int x = (rand() % (Map->getWidth()));
			int y = (rand() % (Map->getHeight()));
			bool duplicate = true;
			while (duplicate)
			{
				duplicate = false;
				for (int k = 0; k < tempList.size(); k++)
				{
					if (tempList.at(k)->getPosition().at(0) == x && tempList.at(k)->getPosition().at(1) == y)
					{
						duplicate = true;
					}
				}
				if (duplicate)
				{
					x = (rand() % (Map->getWidth()));
					y = (rand() % (Map->getHeight()));
				}
			}
			bool stepsReq = false;
			int x_goal = (rand() % (Map->getWidth()));
			int y_goal = (rand() % (Map->getHeight()));
			while (!stepsReq)
			{
				if (abs(x - x_goal) + abs(y - y_goal) == num_steps)
				{
					stepsReq = true;
				}
				else
				{
					x_goal = (rand() % (Map->getWidth()));
					y_goal = (rand() % (Map->getHeight()));
				}
			}
			
			duplicate = true;
			while (duplicate)
			{
				duplicate = false;
				for (int k = 0; k < tempList.size(); k++)
				{
					if ((tempList.at(k)->getGoal().at(0) == x_goal && tempList.at(k)->getGoal().at(1) == y_goal) || (x==x_goal && y==y_goal))
					{
						duplicate = true;
						stepsReq = false;
					}
				}
				if (duplicate)
				{
					while (!stepsReq)
					{
						x_goal = (rand() % (Map->getWidth()));
						y_goal = (rand() % (Map->getHeight()));
						if (abs(x - x_goal) + abs(y - y_goal) == num_steps)
						{
							stepsReq = true;
						}
						/*else
						{
							x_goal = (rand() % (Map->getWidth()));
							y_goal = (rand() % (Map->getHeight()));
						}*/
					}
				}
			}
			int id = 0;
			if (tempList.size() > 0)
			{
				id = tempList.at(tempList.size() - 1)->getID() + 1;
			}
			robot* Robot = new robot(id, 10, 10, x_goal, y_goal);
			
			Robot->setPosition(x, y);
			Robot->setTile(findTileAtPosition(x, y));
			QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(getPositionX().toInt() + 10, getPositionY().toInt(), robot_diameter, robot_diameter);
			QGraphicsEllipseItem* circle_goal = new QGraphicsEllipseItem(getPositionX().toInt() + 10, getPositionY().toInt(), robot_diameter, robot_diameter);
			Robot->setGraphicObject(circle);
			Robot->setGraphicObject_goal(circle_goal);
			tempList.push_back(Robot);
		}
		randomRobots.push_back(tempList);
	}
	return randomRobots;
}

void MainWindow::montecarloTimerEvent()
{

	if (!startStatus && montecarloStatus)
	{
		if (montecarlo_list.size() > 0)
		{
			clearRobots();
			robotList = montecarlo_list.at(0);
			startClicked();
			montecarlo_list.erase(montecarlo_list.begin());
		}
		else
		{
			montecarloStatus = false;
			int numOfSims = getNumberOfSimulations().toInt();
			int numOfRobots = getNumberOfRobots().toInt();
			if (selected_method == 1)
			{
				double path = sumOfAveragePath / numOfSims + 1.0;
				QString pathstr = QString::number(path);
				double time = sumOfTimeOverSims / numOfSims;
				QString timestr = QString::number(time);
				setTimeTextbox(timestr);
				setPathTextbox(pathstr);
			}
			else if (selected_method == 0)
			{
				double path_per_sim = totalPathLRA / numOfSims;
				double path_per_robot = path_per_sim / numOfRobots;
				QString pathstr = QString::number(path_per_robot);
				double time = totalTimeLRA / numOfSims - 1.0;
				QString timestr = QString::number(time);
				setTimeTextbox(timestr);
				setPathTextbox(pathstr);
			}
			
		}
	}
}

template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
	std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
	std::advance(start, dis(g));
	return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	return select_randomly(start, end, gen);
}