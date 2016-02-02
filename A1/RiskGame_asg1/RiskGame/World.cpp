#include <algorithm>
#include "World.h"

World::World(string name):
	_name(name)
{
}

string World::getName()
{
	return _name;
}

map<string, string> World::getInfo()
{
	return _mapInfo;
}

void World::setInfo(map<string, string> mapInfo)
{
	_mapInfo = mapInfo;
}

void World::addTerritory(TerritoryNode* newTerritory)
{
	_territories[newTerritory->getName()] = newTerritory;
}

void World::removeTerritory(TerritoryNode* territory)
{
	vector<TerritoryNode*> adjCountries = territory->getAdjacentTerritories();

	// Remove territory from adjacent territories
	// Assume adjacent countries all in one country
	for (vector<TerritoryNode*>::size_type j=0; j<adjCountries.size(); j++)
	{
		adjCountries[j]->removeAdjacentTerritory(territory);
	}

	// Remove from the list
	_territories.erase(territory->getName());
}

TerritoryNode* World::removeTerritory(string territoryName)
{
	TerritoryNode* terr = NULL;

	if (_territories.find(territoryName) != _territories.end())
	{
		terr = _territories[territoryName];
		this->removeTerritory(terr);
	}
	return terr;
}

void World::addAdjacency(map<string, list<string>> adjacency)
{
	for (map<string, list<string>>::iterator it = adjacency.begin(); it != adjacency.end(); it++)
	{
		if (_territories.find(it->first) == _territories.end())
		{
			cout << "Cannot assign adjacency for unknown territory " << it->first << endl;
			throw;
		}
		list<string> adj = it->second;
		for (list<string>::iterator it2 = adj.begin(); it2 != adj.end(); it2++)
		{
			if (_territories.find(*it2) == _territories.end())
			{
				cout << "Cannot assign adjacency to unknown territory " << *it2 << endl;
				throw;
			}
			_territories[it->first]->addAdjacentTerritory(_territories[*it2]);
		}
	}
}

map<string, Continent*> World::getContinents()
{
	return _continents;
}

Continent* World::getContinent(string continentName)
{
	if (_continents.find(continentName) != _continents.end())
	{
		return _continents[continentName];
	}
	return NULL;
}

void World::addContinent(Continent* continent)
{
	_continents[continent->getName()] = continent;
}

Continent* World::removeContinent(string continentName)
{
	Continent* cont = NULL;
	if (_continents.find(continentName) != _continents.end())
	{
		cont = _continents[continentName];
		_continents.erase(continentName);
	}
	return cont;
}

bool World::check()
{
	// Enforce connected graph
	// Graph nodes are found in _territories
	// Continents are collection of TerritoryNode*, should check if
	// Continents are connected subgraphs, where each country belongs to one and
	// Only one continent

	//Territory cannot exist twice because map<string, TerritoryNode*> allows unique key only for names
	
	return true;
}

void World::print()
{
	cout << "World " << getName();
	if (_continents.size() == 0)
	{
		cout << " does not contain any continent";
	}
	else
	{
		cout << " contains the " << _continents.size() << " following continent: ";
		for (map<string, Continent*>::iterator it = _continents.begin(); it != _continents.end();)
		{
			cout << it->first;
			if ((++it) != _continents.end())
				cout << ", ";
		}
	}
	cout << "." << endl;
}
