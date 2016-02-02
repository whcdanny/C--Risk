#ifndef MAP_INI_H
#define MAP_INI_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include "Continent.h"
#include "TerritoryNode.h"
#include "World.h"
#include "IniParser.h"

using namespace std;

class MapIni
{
	
public:
	MapIni(string fileName);
	map<string, string> getMapInfo();
	map<string, Continent*> getContinents();
	map<string, TerritoryNode*> getTerritories();
	map<string, list<string>> getAdjacency();
	static void writeMapToFile(map<string, string>,
		map<string, Continent*>, string);
	static void writeWorldToFile(World, string);
	~MapIni(void);

private:
	string _fileName;
	map<string, string> _mapInfo;
	map<string, Continent*> _continents;
	map<string, TerritoryNode*> _territories;
	map<string, list<string>> _adjacentTerritories;
	IniParser* _parser;
	void readMapInfo();
	void readContinents();
	void readTerritories();
};

#endif