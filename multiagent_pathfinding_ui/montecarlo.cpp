#include "mainwindow.h"

void MainWindow::monteCarloClicked()
{
	int num_of_robots = getNumberOfRobots().toInt();
	int num_of_steps = getNumberOfSteps().toInt();
	int num_of_simulations = getNumberOfSimulations().toInt();
	montecarlo_list = generateRandomRobots(num_of_robots, num_of_steps, num_of_simulations);
	bool montecarloStatus = true;
}

std::vector<QList<robot*>> MainWindow::generateRandomRobots(int num_robot, int num_steps, int num_simulations)
{
	std::vector<QList<robot*>> randomRobots;
	return randomRobots;
}

void MainWindow::montecarloTimerEvent()
{
	if (!startStatus && montecarloStatus)
	{
		if (montecarlo_list.size() == 0)
		{
			clearRobots();
			robotList = montecarlo_list.at(0);
			startClicked();
			montecarlo_list.erase(montecarlo_list.begin());
		}
		else
		{
			montecarloStatus = false;
		}
	}
}