#include <iostream>
#include "MapIni.h"
#include "TerritoryNode.h"
#include "Continent.h"
#include "World.h"

using namespace std;

void showWorldDetails(World*);
void mainMenu();
void askNewCountry();
void askDefineCountryRelationship();
void askNewContinent();
void askManageContinent();
bool scratch();
bool load();
bool save();

MapIni* loadedMap = NULL;
World* earth = NULL;

int main()
{
	cout<<"Welcome to MapManager"<<endl;
	string answer;
	bool validAnswer = false;


	//Load or start from scratch
	while (!validAnswer)
	{
		cout<<"Do you want to load an existing file (l) or start from scratch (s)?"<<endl;
		getline(cin, answer);
		if (answer.compare("l") == 0) {
			//Load existing file
			validAnswer = load();
		} else if (answer.compare("s") == 0) {
			//Start from scratch
			//Create world
			validAnswer = scratch();
		} else {
			cout<<"I didn't understand"<<endl;
		}
	}

	mainMenu();
	return 0;
}

void mainMenu()
{
	
	cout<<endl;
	cout<<"What do you want to do? Choose from the following list:"<<endl<<endl;
	string answer;

	cout<<"0. Show current configuration"<<endl;
	cout<<"1. Create a country"<<endl;
	cout<<"2. Define the adjacency relationships between countries"<<endl;
	cout<<"3. Create continent"<<endl;
	cout<<"4. Assign countries to a continent"<<endl;
	cout<<"5. Save to file"<<endl;
	cout<<"6. Exit (no saving)"<<endl;
	cout<<endl;
	cout<<"> ";

	getline(cin, answer);
	if (answer.compare("0") == 0) {
		//Show everything
		showWorldDetails(earth);
		mainMenu();
	} else if (answer.compare("1") == 0) {
		//New country
		askNewCountry();
		mainMenu();
	} else if (answer.compare("2") == 0) {
		//Country relationship
		askDefineCountryRelationship();
		mainMenu();
	} else if (answer.compare("3") == 0) {
		//Country relationship
		askNewContinent();
		mainMenu();
	} else if (answer.compare("4") == 0) {
		//Country relationship
		askManageContinent();
		mainMenu();
	} else if (answer.compare("5") == 0) {
		//Save
		save();
		mainMenu();
	} else if (answer.compare("6") == 0) {
		//Exit
		cout<<"Exiting"<<endl;
		//Nothing
	} else {
		cout<<"I didn't understand"<<endl;
		mainMenu(); //Re-ask
	}
}

void showWorldDetails(World* myWorld)
{
	//Print included continents
	myWorld->print();
	cout << endl;

	//Display continents info
	map<string, Continent*> continents = myWorld->getContinents();
	for (map<string, Continent*>::iterator it = continents.begin(); it != continents.end(); ++it)
	{
		it->second->print();

		//Print territories details
		vector<TerritoryNode*> territories = it->second->getTerritories();
		for (vector<TerritoryNode*>::size_type i=0; i<territories.size(); i++)
		{
			territories[i]->print();
		}
		cout << endl;
	}
}

void askNewCountry()
{
	string countryName;
	int countryPosX;
	int countryPosY;
	string tmp;
	vector<string> emptyAdj;

	cout<<"Enter the name of the new country: ";
	getline(cin, countryName);

	cout<<"Enter the X position: ";
	getline(cin, tmp);
	countryPosX = atoi(tmp.c_str());

	cout<<"Enter the Y position: ";
	getline(cin, tmp);
	countryPosY = atoi(tmp.c_str());

	earth->addTerritory(
		new TerritoryNode(countryName, countryPosX, countryPosY));

	cout<<"Country added!"<<endl;
}

void askDefineCountryRelationship()
{
	string answer;
	string c1,c2;
	TerritoryNode *territory1, *territory2;
	cout<<"Existing countries:"<<endl<<endl;
	
	map<string, TerritoryNode*> cont = earth->getTerritories();
	for (map<string, TerritoryNode*>::iterator it = cont.begin(); it != cont.end(); ++it)
	{
		cout<< it->second->getName() << " <"<<it->second->getX()<<","<<it->second->getY()<<"> ";

		//List current adjacency
		cout<<"(";
		it->second->printAdjacency();
		cout<<")"<<endl;
	}

	if (cont.size()<2) {
		cout<<"Need to define at least one more country!"<<endl;
		return;
	}

	cout<<endl;
	cout<<"Enter first country to pair: ";
	getline(cin, c1);;
	cout<<"Enter second country to pair: ";
	getline(cin, c2);

	//Get c1 and c2
	territory1 = earth->getTerritory(c1);
	territory2 = earth->getTerritory(c2);

	if (territory1 != NULL && territory2 != NULL) {
		//Assign each other as adjacent country
		territory1->addAdjacentTerritory(territory2);
		territory2->addAdjacentTerritory(territory1);

		cout<<"Paired!"<<endl;
	} else {
		cout<<"Couldn't find one of the countries"<<endl;
	}
}

void askNewContinent()
{
	string continentName, tmp;
	int score;

	cout<<"Enter the name of the new continent: ";
	getline(cin, continentName);

	cout<<"Enter score for owning the continent: ";
	getline(cin, tmp);
	score = atoi(tmp.c_str());

	earth->addContinent(new Continent(continentName, score));

	cout<<"Continent created!"<<endl;
}

void askManageContinent()
{
	string answer;
	string continentName;
	string countryName;

	cout<<"Existing continents:"<<endl;
	map<string, Continent*> cont = earth->getContinents();
	for (map<string, Continent*>::iterator it = cont.begin(); it != cont.end(); ++it)
	{
		cout << it->second->getName() << endl;
	}
	cout<<endl;

	cout<<"Unassigned countries:"<<endl;
	map<string, TerritoryNode*> terr = earth->getTerritories();
	for (map<string, TerritoryNode*>::iterator it = terr.begin(); it != terr.end(); ++it)
	{
		bool isAssigned = false;
		for (map<string, Continent*>::iterator it2 = cont.begin(); it2 != cont.end(); ++it2)
		{
			if (it2->second->isInContinent(it->second)) {
				isAssigned = true;
				break;
			}
		}

		if (!isAssigned) {
			cout << it->second->getName() << " ";
			cout<<"(";
			it->second->printAdjacency();
			cout<<")"<<endl;
		}
	}
	
	cout<<endl;
	cout<<"Enter the continent you want to assign a country to: ";
	getline(cin, continentName);

	Continent* continent = NULL;
	if ((continent = earth->getContinent(continentName)) == NULL) {
		cout<<"Continent doesn't exist"<<endl;
		return;
	}

	cout<<"Enter the country you want to assign to "<<continent->getName()<<": ";
	getline(cin, countryName);

	TerritoryNode* territory = NULL;
	if ((territory = earth->getTerritory(countryName)) == NULL) {
		cout<<"Country doesn't exist"<<endl;
		return;
	}

	continent->addTerritory(territory);

	cout<<"The country "<<territory->getName()<<" was added to the continent "
		<<continent->getName()<<"!"<<endl;
}

bool scratch()
{
	earth = new World("Earth");
	map<string, string> mapInfo;
	mapInfo["author"] = "MapManager";
	earth->setInfo(mapInfo);
	return true;
}

bool load()
{
	string fileName;
	cout<<"Enter the location of the file to load: ";
	getline(cin, fileName);
	try
	{
		//Load map
		loadedMap = new MapIni(fileName);
		//Create world
		earth = new World("Earth");

		//Retrieve information
		earth->setInfo(loadedMap->getMapInfo());
		map<string, TerritoryNode*> territories = loadedMap->getTerritories();
		map<string, list<string>> adjacency = loadedMap->getAdjacency();
		map<string, Continent*> continents = loadedMap->getContinents();

		//list territories and fill the world
		for (map<string, TerritoryNode*>::iterator it = territories.begin();it != territories.end(); ++it)
		{
			//Add territory to world
			earth->addTerritory(it->second);
		}

		//Assign adjacency
		earth->addAdjacency(adjacency);

		//List continents and fill the world
		for (map<string, Continent*>::iterator it = continents.begin(); it != continents.end(); ++it)
		{
			//Add continent to world
			earth->addContinent(it->second);
		}
		delete loadedMap;
	} catch (...)
	{
		if (loadedMap != NULL)
		{
			delete loadedMap;
			loadedMap = NULL;
		}
		if (earth != NULL)
		{
			delete earth;
			earth = NULL;
		}
		return false;
	}
	cout << "Loaded successfully!" << endl;
	return true;
}

bool save()
{
	string fileName;
	cout<<"Enter the location of the file to save: ";
	getline(cin, fileName);

	try
	{
		MapIni::writeWorldToFile(*earth, fileName);
	} catch (...)
	{
		return false;
	}
	cout << "Saved!" << endl;
	return true;
}
