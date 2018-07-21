#ifndef RIPCITYEVENT_H_
#define RIPCITYEVENT_H_
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Player.h"


class RipCityEvent
{
private:
	std::vector<std::string> names;

protected:
	std::vector<Player *> Players;
	double total_time;
	double reg_time;
	

public:
	RipCityEvent()
	{
		total_time = 0;
		reg_time = 0;
	}

	//// this is where all the names will be assigned, and put into a data structure
	//// download the txt files of the first and last names, randomly select them and put them in a data structure.

	///Download names
	///add to vector
	/// This is the "registration" and set-up function part
	/// registration being the people that have attended the event, not just the people 
	// who will shoot in the competition.
	void Registration() {
		std::string lineFirst;
		std::string lineLast;
		std::string name;
		std::ifstream firstnames("residents_of_273ville.txt");
		std::ifstream lastnames("surnames_of_273ville.txt");
		if (firstnames.is_open() && lastnames.is_open())
		{
			while (std::getline(firstnames, lineFirst) && std::getline(lastnames, lineLast))
			{
				name = lineFirst + " " + lineLast;
				names.push_back(name);
			}
			firstnames.close();
			lastnames.close();
		}

		else std::cout << "Unable to open file";

		std::cout << "How many hours will the event be?" << std::endl;
		std::cin >> total_time;
		total_time = (total_time - 1) * 60 * 60; ///the minus one is for saying there will be an hour delay 
												//// between when the event starts and when the shooting begins
												//// giving enough people to be registered before it starts
												//// so that the baskets will be in use the whole time

		//this is to create the different players with all of there information
		// in this case, so far, just their name and the % of shots each will choose to take at different spots 
		for (int i = 0; i < names.size(); i++)
		{
			Players.push_back(new Player(names[i]));
		}

	}
	
	/// Both of these functions would be used over all competitions held at 
	///  this event
	virtual void EventFunction() = 0;
	virtual void SetTimes() = 0;
	virtual void TheStats() = 0;

};


#endif