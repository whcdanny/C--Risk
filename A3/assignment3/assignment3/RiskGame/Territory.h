#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Territory
{
public:
	Territory(string, int, int);
	void setName(string);
	string getName();
	void setCoordinates(int, int);
	int getX();
	int getY();
	const vector<Territory>& getAdjacentterritories();
	const vector<string>& getAdjacentterritoriesName();
	void addAdjacentTerritory(Territory);
	void addAdjacentTerritoryName(string);
	void removeAdjacentTerritory(Territory);
	void print();

private:
	string _name;
	int _posX;
	int _posY;
	vector<Territory> _adjacentTerritories;
	vector<string> _adjacentTerritoriesName;
};
