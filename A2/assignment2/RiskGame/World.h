#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <string>
#include <map>
#include <list>
#include "Continent.h"
#include "TerritoryNode.h"
using namespace std;

class World
{
	
public:
	World(string);
	string getName();
	map<string, string> getInfo();
	void setInfo(map<string, string>);

	map<string, TerritoryNode*> getTerritories();
	TerritoryNode* getTerritory(string);
	void addTerritory(TerritoryNode*);
	void removeTerritory(TerritoryNode*);
	TerritoryNode* removeTerritory(string);
	
	void addAdjacency(map<string, list<string>>);
	
	map<string, Continent*> getContinents();
	Continent* getContinent(string);
	void addContinent(Continent*);
	Continent* removeContinent(string);
	void destroyContinent(string);
	
	bool check();
	void print();

private:
	string _name;
	map<string, TerritoryNode*> _territories;
	map<string, Continent*> _continents;
	map<string, string> _mapInfo;
};

#endif