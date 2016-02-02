#ifndef CONTINENT_H
#define CONTINENT_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "TerritoryNode.h"
using namespace std;

class Continent
{
public:
	Continent(string, int);
	string getName();
	int getBonus();
	vector<TerritoryNode*> getTerritories();
	void addTerritory(TerritoryNode*);
	void removeTerritory(TerritoryNode*);
	TerritoryNode* removeTerritory(string);
	void print();

private:
	string _name;
	int _bonusOwning;
	vector<TerritoryNode*> _territories;
};

#endif