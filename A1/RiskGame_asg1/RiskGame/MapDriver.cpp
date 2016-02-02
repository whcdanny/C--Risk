//COMP 345 Assignment1 Part 4 save/load
//Name: Haochen Wang
//DATE: 2015/10/28


#include <iostream>
#include <map>
#include "Continent.h"
#include "TerritoryNode.h"
#include "World.h"
#include "MapIni.h"

using namespace std;

void createWorldFromMap(World& myWorld, MapIni* myMap);
void showWorldDetails(World& myWorld);

int main(int argc, char* argv[])
{
	cout << "RiskGame Map parser" << endl << endl;
	MapIni *myMap;
	myMap = new MapIni("..\\resources\\World.map");
	
	// Create world
	World myWorld("Earth");
	createWorldFromMap(myWorld, myMap);
	delete myMap;

	// Print world details
	showWorldDetails(myWorld);

	// Get North America
	Continent* na = myWorld.getContinent("North America");
	if (na == NULL)
	{
		cout << "Could not find North America in the world." << endl;
	}

	// Delete a territory from a continent
	cout << endl << "Deleting Quebec from North America" << endl;
	TerritoryNode* qc = na->removeTerritory("Quebec");
	// Delete from the whole world
	myWorld.removeTerritory(qc);
	delete qc;

	// Write new world to file
	cout << "Write modified world to file" << endl;
	MapIni::writeWorldToFile(myWorld, "..\\resources\\newWorld.map");

	cin.get();
	return EXIT_SUCCESS;
}

void createWorldFromMap(World& myWorld, MapIni* myMap)
{
	// Retrieve info
	myWorld.setInfo(myMap->getMapInfo());
	map<string, TerritoryNode*> territories = myMap->getTerritories();
	map<string, list<string>> adjacency = myMap->getAdjacency();
	map<string, Continent*> continents = myMap->getContinents();

	// List territories and fill the world
	for (map<string, TerritoryNode*>::iterator it = territories.begin();it != territories.end(); ++it)
	{
		// Add territory to world
		myWorld.addTerritory(it->second);
	}

	// Assign adjacency
	myWorld.addAdjacency(adjacency);

	// List continents and fill the world
	for (map<string, Continent*>::iterator it = continents.begin(); it != continents.end(); ++it)
	{
		// Add continent to world
		myWorld.addContinent(it->second);
	}
}

void showWorldDetails(World& myWorld)
{
	// Print included continents
	myWorld.print();
	cout << endl;

	// Display continents info
	map<string, Continent*> continents = myWorld.getContinents();
	for (map<string, Continent*>::iterator it = continents.begin(); it != continents.end(); ++it)
	{
		it->second->print();

		// Print territories details
		vector<TerritoryNode*> territories = it->second->getTerritories();
		for (vector<TerritoryNode*>::size_type i=0; i<territories.size(); i++)
		{
			territories[i]->print();
		}
		cout << endl;
	}
}
