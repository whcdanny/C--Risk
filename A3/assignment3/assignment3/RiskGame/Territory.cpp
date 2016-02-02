#include <algorithm>
#include "Territory.h"

Territory::Territory(string name, int posX, int posY):
	_name(name),
	_posX(posX),
	_posY(posY)
{
}

void Territory::setName(string name)
{
	_name = name;
}

string Territory::getName()
{
	return _name;
}

void Territory::setCoordinates(int posX, int posY)
{
	_posX = posX;
	_posY = posY;
}

int Territory::getX()
{
	return _posX;
}

int Territory::getY()
{
	return _posY;
}

	vector<Territory> getAdjacentterritories();
	void addAdjacentTerritory(Territory);
	void removeAdjacentTerritory(Territory);
	void print();

const vector<Territory>& Territory::getAdjacentterritories()
{
	return _adjacentTerritories;
}

void Territory::addAdjacentTerritory(Territory newTerritory)
{
	_adjacentTerritories.push_back(newTerritory);
}

const vector<string>& Territory::getAdjacentterritoriesName()
{
	return _adjacentTerritoriesName;
}

void Territory::addAdjacentTerritoryName(string newTerritory)
{
	_adjacentTerritoriesName.push_back(newTerritory);
}

void Territory::removeAdjacentTerritory(Territory territory)
{
	for (size_t i = 0; i < _adjacentTerritories.size(); i++)
	{
		if (_adjacentTerritories[i].getName() == territory.getName())
			_adjacentTerritories.erase(_adjacentTerritories.begin()+(i-1));
	}
}

void Territory::print()
{
	cout << "Territory " << getName();
	cout << " center positioned at: ("<<getX()<<","<<getY()<<")";
	if (_adjacentTerritories.size() == 0)
	{
		cout << " does not have any adjacent territories";
	}
	else
	{
		cout << " is adjacent to the " << _adjacentTerritories.size() << " following territories: ";
		for(vector<Territory>::iterator it = _adjacentTerritories.begin(); it != _adjacentTerritories.end(); it++)
		{
			cout << it->getName() << ", ";
		}
	}
	cout << endl;
}
