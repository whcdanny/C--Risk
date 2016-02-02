#include "MapIni.h"
#include "IniWriter.h"

using namespace std;

MapIni::MapIni(string fileName)
{
	_parser = NULL;

	try
	{
		_parser = new IniParser(fileName);
	}
	catch (IniParser::Exception e)
	{
		switch (e)
		{
		case IniParser::Exception::FILE_NOT_FOUND:
			cout << "Error: The parser could not open the file " << fileName << endl;
			throw;
		case IniParser::Exception::FILE_UNREADABLE:
			cout << "Error: The parser was unable to read the file " << fileName << endl;
			throw;
		case IniParser::Exception::MALFORMED_SECTION:
			cout << "Error: The file " << fileName << " contains malformed sections" << endl;
			throw;
		case IniParser::Exception::MALFORMED_KEY_VALUE:
			cout << "Error: The file " << fileName << " contains malformed key-value pairs" << endl;
			throw;
		}
	}

	readMapInfo();
	readContinents();
	readTerritories();

	delete _parser;
}

void MapIni::readMapInfo()
{
	//Check for the Map section
	set<string> sectionNames = _parser->getSectionsName();
	if (sectionNames.find("Map") == sectionNames.end())
	{
		cout << "The configuration file lacks a Map section" << endl;
		throw;
	}

	//Copy
	_mapInfo = _parser->getSection("Map");
}

void MapIni::readContinents()
{
	//Check for the Continents section
	set<string> sectionNames = _parser->getSectionsName();
	if (sectionNames.find("Continents") == sectionNames.end())
	{
		cout << "The configuration file lacks a Continents section" << endl;
		throw;
	}

	map<string, string> continents = _parser->getSection("Continents");

	//Create a continent objects
	for (map<string, string>::iterator it = continents.begin(); it != continents.end(); ++it)
	{
		Continent *newContinent = new Continent(it->first, atoi(it->second.c_str()));
		_continents[it->first] = newContinent;
	}
}

void MapIni::readTerritories()
{
	//Check for the Territories section
	set<string> sectionNames = _parser->getSectionsName();
	if (sectionNames.find("Territories") == sectionNames.end())
	{
		cout << "The configuration file lacks a Territories section" << endl;
		throw;
	}

	map<string, string> territories = _parser->getSection("Territories");

	//Create a territories objects
	for (map<string, string>::iterator it = territories.begin(); it != territories.end(); ++it)
	{
		string name, continent;
		int posX, posY;
		list<string> adj;
		
		//Parse line
		istringstream iss(it->second);
		int i=0;
		for (string token; getline(iss, token, ','); i++)
		{
			switch (i)
			{
			case 0:
				name = move(token);
				break;
			case 1:
				posX = atoi(token.c_str());
				break;
			case 2:
				posY = atoi(token.c_str());
				break;
			case 3:
				continent = move(token);
				break;
			default:
				adj.push_back(token);
				break;
			}
		}

		//Check if territory name doesn't already exist
		if (_territories.find(name) != _territories.end())
		{
			cout << "Territory " << name << " is declared twice!" << endl;
			throw;
		}

		//Create new territory
		TerritoryNode* newTerr = new TerritoryNode(name, posX, posY);
		
		_adjacentTerritories[name] = adj;

		//Check if territory belongs to existing continents, and add it
		if (_continents.find(continent) != _continents.end())
		{
			_continents[continent]->addTerritory(newTerr);
		} else {
			cout << "Country " << name << " belong to unknown continent " << continent << endl;
			throw;
		}
		
		//Save
		_territories[name] = newTerr;
		

	} //Iterator over territories
}

map<string, string> MapIni::getMapInfo()
{
	return _mapInfo;
}

map<string, Continent*> MapIni::getContinents()
{
	return _continents;
}

map<string, TerritoryNode*> MapIni::getTerritories()
{
	return _territories;
}

map<string, list<string>> MapIni::getAdjacency()
{
	return _adjacentTerritories;
}

void MapIni::writeMapToFile(map<string, string> mapInfo,
							map<string, Continent*> continents,
							string fileName)
{
	map<string, string> continentsDesc;
	map<string, set<string>> territoriesDescByContinent;

	//Prepare continents
	for (map<string, Continent*>::iterator it = continents.begin(); it != continents.end(); ++it)
	{
		continentsDesc[it->first] = to_string(it->second->getBonus());

		//Prepare territories
		vector<TerritoryNode*> territories = it->second->getTerritories();
		for (vector<TerritoryNode*>::size_type i=0; i<territories.size(); i++)
		{
			ostringstream os;
			os << territories[i]->getName() << ","
				<< territories[i]->getX() << ","
				<< territories[i]->getY() << ","
				<< it->first;

			vector<TerritoryNode*> adjTerr = territories[i]->getAdjacentTerritories();
			for (vector<TerritoryNode*>::size_type j=0; j<adjTerr.size(); j++)
			{
				os << "," << adjTerr[j]->getName();
			}
			territoriesDescByContinent[it->first].insert(os.str());
		}
	}

	try
	{
		IniWriter writer(fileName);
		
		//Write Map section
		writer.writeSectionKeyValuePair("Map", mapInfo);

		//Write Continents
		writer.writeSectionKeyValuePair("Continents", continentsDesc);

		//Write Territories
		writer.writeSectionRaw("Territories" , territoriesDescByContinent);

		//Close file
		writer.close();
	} catch (IniWriter::Exception e)
	{
		switch (e)
		{
		case IniWriter::Exception::FILE_ACCESS_DENIED:
			cout << "Error: Could not open the file " << fileName << " for writing." << endl;
			throw;
		case IniWriter::Exception::FILE_UNWRITABLE:
			cout << "Error: Something occurred while writing to the file " << fileName << endl;
			throw;
		}
	}
}

void MapIni::writeWorldToFile(World world, string fileName)
{
	MapIni::writeMapToFile(world.getInfo(), world.getContinents(), fileName);
}

MapIni::~MapIni(void)
{
	//Assume caller will delete continents and territories
}
