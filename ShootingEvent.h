#ifndef SHOOTINGEVENT_H_
#define SHOOTINGEVENT_H_
#include "RipCityEvent.h"
#include <iostream>
#include <ctime>
#include <map>
#include <utility>
#include <queue>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <stack>

class ShootingEvent : public RipCityEvent
{
private:
	double time_between_ppl;
	double time_shooting;
	double time_between_shots; 
	double FGpercentage; 
	double finalscore;
	int baskets;
	int totalshots;
	std::map<std::string, int> MadeShot;
	std::priority_queue<int> Podium;

public:
	ShootingEvent()
	{
		time_between_ppl = 0;
		time_shooting = 0; 
		time_between_shots = 0;
		FGpercentage = 0; 
		finalscore = 0;
		baskets = 0;
		totalshots = 0;
	}

	///Have user determine the time everything will take, this will be in the free throw class

	void SetTimes()
	{

		std::cout << "How long will the time be between shooters? (min):" << std::endl;
		std::cin >> time_between_ppl;
		time_between_ppl = time_between_ppl * 60; // seconds

		std::cout << "How long will the shooters have to shoot? (min):" << std::endl;
		std::cin >> time_shooting;
		time_shooting = time_shooting * 60; // seconds
											
		std::cout << "How many baskets will there be?" << std::endl;
		std::cin >> baskets;

	}
	

	
	void EventFunction()
	{
		///Select people who will shoot, assign a time that will determine how fast the person gets their shot off
		srand(time(NULL));
		for (int i = 0; i < Players.size(); i++)
		{	

			///lay-ins
			if (Players[i]->getLayinPerc() != 0) {

				time_between_shots = 1;
				FGpercentage = ((rand() % 3500) + 4500) * .0001;
				totalshots = totalshots + ((time_shooting * (Players[i]->getLayinPerc()) / 100) / time_between_shots);
				int layInshots = ((time_shooting * (Players[i]->getLayinPerc()) / 100) / time_between_shots) * FGpercentage;
				Players[i]->setlayInMade(layInshots);
				finalscore = finalscore + layInshots;

			}
			else
				Players[i]->setlayInMade(0);


			///free-throw
		if (Players[i]->getfreeThrowPerc() != 0) {
			time_between_shots = 3;
			FGpercentage = ((rand() % 3500) + 3000) * .0001;
			totalshots = totalshots + ((time_shooting * (Players[i]->getfreeThrowPerc()) / 100) / time_between_shots);
			int freethrowshots = ((time_shooting * (Players[i]->getfreeThrowPerc()) / 100) / time_between_shots) * FGpercentage;
			Players[i]->setfreeThrowMade(freethrowshots);
			//Free-Throw worth two points
			finalscore = finalscore + (freethrowshots * 2);
		}
		else
			Players[i]->setfreeThrowMade(0);
			

			////3Pt
		if (Players[i]->getThreePtPerc() != 0) {
			time_between_shots = 3;
			FGpercentage = ((rand() % 3000) + 2000) * .0001;
			totalshots = totalshots + ((time_shooting * (Players[i]->getThreePtPerc()) / 100) / time_between_shots);
			int threePtshots = ((time_shooting * (Players[i]->getThreePtPerc()) / 100) / time_between_shots) * FGpercentage;
			Players[i]->setThreePtMade(threePtshots);
			//3pt worth 3 points
			finalscore = finalscore + (threePtshots * 3);
		}
		else
			Players[i]->setThreePtMade(0);

			//// half-court
		if (Players[i]->getHalfPerc() != 0) {
			time_between_shots = 4;
			FGpercentage = (rand() % 1000) *0.0001;
			totalshots = totalshots + ((time_shooting * (Players[i]->getHalfPerc()) / 100) / time_between_shots);
			int halfshots = ((time_shooting * (Players[i]->getHalfPerc()) / 100) / time_between_shots) * FGpercentage * 4;
			Players[i]->setHalfMade(halfshots);
			// Half court worth 4 points
			finalscore = finalscore + (halfshots * 4);
		}
		else
			Players[i]->setHalfMade(0);
			
			MadeShot.insert(make_pair(Players[i]->getName(), finalscore));
			total_time = total_time - ((time_shooting + time_between_ppl) / baskets); ///divided by baskets to represent 
			if (total_time <= 0)														/// all the baskets to shoot on
				break;

		}

		//List in alphabetical order, by first name
		//first priority queue
		std::priority_queue<std::string> NAMES;
		for (int i = 0; i < MadeShot.size(); i++)
			NAMES.push(Players[i]->getName());
		//then flip order in a stack to display correctly
		std::stack<std::string> NameList;
		for (int i = 0; !NAMES.empty(); i++)
		{
			NameList.push(NAMES.top());
			NAMES.pop();
		}
			
		std::cout << "First, here is a list of the participants in alphabetical order, for the convenience of " << std::endl;
		std::cout << "finding your friends and or family:" << std::endl;
		for (int i = 0; i < MadeShot.size(); i++)
		{
			std::cout << NameList.top() << " " << MadeShot[NameList.top()] << std::endl;
			NameList.pop();
		}
		std::cout << std::endl;

		///Priority queue the results of the highest score.
		std::cout << "Now for the podium listing: " << std::endl;
		for (int i = 0; i < MadeShot.size(); i++)
			Podium.push(MadeShot[Players[i]->getName()]);

		
		///Display the results from first to last
		std::map<std::string, int>::iterator it = MadeShot.begin();
		std::map<std::string, int>::iterator it2 = MadeShot.end();
		it2--;
		while (!Podium.empty())
		{
			if (Podium.top() == it->second)
			{
				std::cout << it->first << " " << it->second << std::endl;
				Podium.pop();
			}

			if (it == it2)
				it = MadeShot.begin();
			else
				it++;
		}

		char breakup;
		std::cout << "(Once you are done looking at the results, Please enter any letter " << std::endl;
		std::cout << "to let the next part of program run)" << std::endl;
		std::cin >> breakup;
		// generate random number
		int winner = rand() % MadeShot.size();
		///pick a random name out of the queue, that will win a free car.
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "Also we have a raffle for the participants in the shooting competition!" << std::endl
			<< "The prize is an all new 2019 Toyota RAV4, sponsored by your local Toyota of Portland dealership!!" << std::endl
			<< "And the winner, of the all new RAV4 is ";
		for (int i = 0; i < 5; i++)
		{
			Sleep(1000);
			std::cout << ". ";
		}
		Sleep(1000);
		std::cout << Players[winner]->getName() << std::endl
			<< "Congrats you've won!" << std::endl;
	}
	
	void TheStats()
	{
		std::cout << std::endl;
		///How many people participated
		std::cout << "There were a total of " << MadeShot.size() << " people who shot in this event." << std::endl;

		///show average of how many of each shot was made and the average FG percentage
	
		int totallayinMADE = 0;
		int totalthreeptMADE = 0;
		int totalfreethrowMADE = 0;
		int totalhalfMADE = 0;
		for (int i = 0; i < MadeShot.size(); i++) {
			totallayinMADE = totallayinMADE + Players[i]->getlayinMade();
			totalthreeptMADE = totalthreeptMADE + Players[i]->getThreePointMade();
			totalfreethrowMADE = totalfreethrowMADE + Players[i]->getFreeThrowMade();
			totalhalfMADE = totalhalfMADE + Players[i]->getHalfMade();
		}
		double totalShots = totalshots;
		double FGperc = (totallayinMADE + totalfreethrowMADE + totalhalfMADE + totalthreeptMADE) / totalShots;
		std::cout << "Total shots taken: " << totalshots << std::endl;
		std::cout << "Total shots made: " << totallayinMADE + totalfreethrowMADE + totalhalfMADE + totalthreeptMADE << std::endl;
		std::cout << "Field goal percentage of all shots: " << FGperc * 100.0 << "%" << std::endl;
		std::cout << "Total lay-ins made: " << totallayinMADE << std::endl;
		std::cout << "Total free throws made: " << totalfreethrowMADE << std::endl;
		std::cout << "Total three points made: " << totalthreeptMADE << std::endl;
		std::cout << "Total half court shots made: " << totalhalfMADE << std::endl;
		double AVGpoint = 0;

		for (int i = 0; i < MadeShot.size(); i++)
			AVGpoint = AVGpoint + MadeShot[Players[i]->getName()] / MadeShot.size();
		std::cout << "Average point total: " << AVGpoint << std::endl;

	}
};
#endif