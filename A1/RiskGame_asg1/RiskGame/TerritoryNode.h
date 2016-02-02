#ifndef TERRITORY_NODE_H
#define TERRITORY_NODE_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TerritoryNode
{
	
public:
	TerritoryNode(string, int, int);
	string getName();
	int getX();
	int getY();
	void addAdjacentTerritory(TerritoryNode*);
	bool isAdjacentTerritory(TerritoryNode*);
	vector<TerritoryNode*> getAdjacentTerritories();
	void removeAdjacentTerritory(TerritoryNode*);
	void print();

private:
	string _name;
	int _posX;
	int _posY;
	vector<TerritoryNode*> _adjacentTerritories;
};

#endif