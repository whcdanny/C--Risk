#include "MapParser.h"

using namespace std;

MapParser::MapParser(string fileName) {
	_fileName = fileName;
	vector<string> continent_inf, temp,country_inf,sub_country,mathContient;

	ifstream fileStream(fileName);
	
	string str;
	if (!fileStream.is_open())
	{
		cout << "Cannot read file" << endl;
	}

	// read line by line
	while (getline(fileStream, str))
	{
		temp.push_back(str);
		if (str=="[Territories]") //check start in Territories
		{
			readTerritories(fileStream);
		}
	}

	fileStream.close();
}

void MapParser::readTerritories(ifstream& fileStream)
{
	string line;
	while (getline(fileStream, line))
	{
		if (line != "") continue;

		string name, continent;
		int posX, posY;
		vector<string> adj;
		
		// parse line
		istringstream iss(line);
		int i=0;
		for (string token; getline(iss, token, ','); i++)
		{
			switch (i)
			{
			case 0:
				name = token;
				break;
			case 1:
				posX = atoi(token.c_str());
				break;
			case 2:
				posY = atoi(token.c_str());
				break;
			case 3:
				continent = token;
				break;
			default:
				adj.push_back(token);
			}
		}

		//create new territory
		Territory* newTerr = new Territory(name, posX, posY);
		for (int i=0; i<adj.size(); i++)
			newTerr->addAdjacentTerritoryName(adj[i]);

		//save
		_territories.push_back(newTerr);
		newTerr->print();
	}		
}

//map<string, string> MapParser::getMapInfo() {
//
//}

//vector<Continent*> MapParser::getContinents() {
//	return null;
//}

vector<Territory*> MapParser::getTerritories() {
	return _territories;
}
