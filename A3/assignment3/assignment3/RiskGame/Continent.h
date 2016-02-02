#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Territory.h"
using namespace std;

class Continent
{
public:
	Continent(string, int);
	void setName(string);
	string getName();
	void setBonus(int);
	int getBonus();
	const vector<Territory>& getTerritories();
	void addTerritory(Territory);
	void removeTerritory(Territory);
	void print();

private:
	string _name;
	int _bonusOwning;
	vector<Territory> _territories;
};
