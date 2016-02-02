#include <algorithm>
#include "Continent.h"

Continent::Continent(string name, int bonus):
	_name(name),
	_bonusOwning(bonus)
{
}

string Continent::getName()
{
	return _name;
}

int Continent::getBonus()
{
	return _bonusOwning;
}

vector<TerritoryNode*> Continent::getTerritories()
{
	return _territories;
}

void Continent::addTerritory(TerritoryNode* newTerritory)
{
	_territories.push_back(newTerritory);
}

bool Continent::isInContinent(TerritoryNode* territory)
{
	for (vector<TerritoryNode*>::size_type i=0; i<_territories.size(); i++)
	{
		if (_territories[i]->getName() == territory->getName())
			return true;
	}
	return false;
}

void Continent::removeTerritory(TerritoryNode* territory)
{
	for (vector<TerritoryNode*>::size_type i=0; i<_territories.size(); i++)
	{
		if (_territories[i]->getName() == territory->getName()) {
			_territories.erase(_territories.begin() + i);
			break;
		}
	}
}

TerritoryNode* Continent::removeTerritory(string territoryName)
{
	TerritoryNode* terr;

	//Remove territory from list
	for (vector<TerritoryNode*>::size_type i=0; i<_territories.size(); i++)
	{
		if (_territories[i]->getName() == territoryName) {
			vector<TerritoryNode*> adjCountries = _territories[i]->getAdjacentTerritories();

			//Remove territory from adjacent territories
			//Assume adjacent countries are reciprocal
			for (vector<TerritoryNode*>::size_type j=0; j<adjCountries.size(); j++)
			{
				adjCountries[j]->removeAdjacentTerritory(_territories[i]);
			}

			terr = _territories[i];
			_territories.erase(_territories.begin() + i);
			i--;
		}
	}

	return terr;
}

void Continent::print()
{
	cout << "Continent " << getName();
	cout << " has " << getBonus() << " points of bonus for owning one of its territories,";
	if (_territories.size() == 0)
	{
		cout << " does not contain any territory";
	}
	else
	{
		cout << " contains the " << _territories.size() << " following territories: ";
		for (vector<TerritoryNode*>::size_type i=0; i<_territories.size(); i++)
		{
			cout << _territories.at(i)->getName();
			if (i+1 != _territories.size())
				cout << ", ";
		}
	}
	cout << "." << endl;
}
