// FinalProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include "RipCityEvent.h"
#include "ShootingEvent.h"
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <map>
#include <queue>
#include <list>
int main()
{
	std::cout << "Welcome to the Portland Trail Blazers free throw competition! Everyone who enters is able to "
		<< "participate. " << std::endl <<
		"Each person shoot's for a certain amount of time, lay-ins are worth one point, free-throws two, " << std::endl <<
		"three-pointers 3, and half court shots are 4, and whoever finishes with the most makes will win "
		<< "a signed Damian Lilliard jersey and two season tickets for this upcoming 2018-2019 season." 
		<< " Good luck and Go Rip City!" << std::endl;


	RipCityEvent * shooting = new ShootingEvent();
	shooting->Registration();
	shooting->SetTimes();
	shooting->EventFunction();
	shooting->TheStats();


}

