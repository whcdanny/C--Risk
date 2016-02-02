#include <algorithm>
#include "Continent.h"

//Create a new Continent
Continent::Continent(string name, int bonus):
	_name(name),
	_bonusOwning(bonus)
{
}

//Set name
void Continent::setName(string name)
{
	_name = name;
}

//Get name
string Continent::getName()
{
	return _name;
}

//Set Bonus
void Continent::setBonus(int bonusOwning){
		_bonusOwning=bonusOwning;
}

//Get Bonus
int Continent::getBonus()
{
	return _bonusOwning;
}

//Get territories from territory class
const  vector<Territory>& Continent::getTerritories(){
	return _territories;
}

//Add territories 
void Continent::addTerritory(Territory newTerritory){
	_territories.push_back(newTerritory);
}

//Remove territories
void Continent::removeTerritory(Territory territory){
	for (size_t i=0; i<_territories.size(); i++)
	{
		if (_territories[i].getName() == territory.getName()) {
			_territories.erase(_territories.begin() + i);
			break;
		}
	}
}

//Continent print
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
		for (vector<Territory>::size_type i=0; i<_territories.size(); i++)
		{
			cout << _territories.at(i).getName();
			if (i+1 != _territories.size())
				cout << ", ";
		}
	}
	cout << "." << endl;
}