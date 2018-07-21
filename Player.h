#ifndef Player_H_
#define Player_H_
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <string>


class Player
{
private:
	int LayInMade;
	int LayInPercent;
	int FreeThrowMade;
	int FreeThrowPercent;
	int ThreePtMade;
	int ThreePtPercent;
	int HalfMade;
	int HalfPercent;
	std::string name;
	int totalmakes;

public:
	Player()
	{

	}

	Player(std::string name)
	{
		this->name = name;
		while ((LayInPercent + FreeThrowPercent + ThreePtPercent + HalfPercent) != 100) {
			LayInPercent = rand() % 100;
			FreeThrowPercent = rand() % 100;
			ThreePtPercent = rand() % 100;
			HalfPercent = rand() % 100;
		}
	}

	int getLayinPerc()
	{
		return LayInPercent;
	}

	int getfreeThrowPerc()
	{
		return FreeThrowPercent;
	}

	int getThreePtPerc()
	{
		return ThreePtPercent;
	}

	int getHalfPerc()
	{
		return HalfPercent;
	}

	void setlayInMade(int made)
	{
		LayInMade = made;
	}

	void setfreeThrowMade(int made)
	{
		FreeThrowMade = made;
	}

	void setThreePtMade(int made)
	{
		ThreePtMade = made;
	}

	void setHalfMade(int made)
	{
		HalfMade = made;
	}

	std::string getName()
	{
		return name;
	}

	int getlayinMade()
	{
		return LayInMade;
	}

	int getFreeThrowMade()
	{
		return FreeThrowMade;
	}

	int getThreePointMade()
	{
		return ThreePtMade;
	}

	int getHalfMade()
	{
		return HalfMade;
	}
	
	int getTotalMakes()
	{
		totalmakes = HalfMade + ThreePtMade + FreeThrowMade + LayInMade;
		return totalmakes;
	}
};

#endif