#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include "Continent.h"
#include "Territory.h"

using namespace std;

class MapParser
{
public:
	MapParser(string fileName);
	map<string, string> getMapInfo();
	vector<Continent*> getContinents();
	vector<Territory*> getTerritories();
	~MapParser(void);

private:
	string _fileName;
	vector<Territory*> _territories;
	void MapParser::readTerritories(ifstream&);
};
