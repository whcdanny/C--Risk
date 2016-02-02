#include "TerritoryNode.h"

TerritoryNode::TerritoryNode(string name, int posX, int posY):
	_name(name),
	_posX(posX),
	_posY(posY)
{}

string TerritoryNode::getName()
{
	return _name;
}

int TerritoryNode::getX()
{
	return _posX;
}

int TerritoryNode::getY()
{
	return _posY;
}

void TerritoryNode::addAdjacentTerritory(TerritoryNode* newTerritory)
{
	if (!this->isAdjacentTerritory(newTerritory))
		_adjacentTerritories.push_back(newTerritory);
}

bool TerritoryNode::isAdjacentTerritory(TerritoryNode* newTerritory)
{
	for (vector<TerritoryNode*>::size_type i=0; i<_adjacentTerritories.size(); i++)
	{
		if (_adjacentTerritories[i]->getName() == newTerritory->getName())
			return true;
	}
	return false;
}

vector<TerritoryNode*> TerritoryNode::getAdjacentTerritories()
{
	return _adjacentTerritories;
}

void TerritoryNode::removeAdjacentTerritory(TerritoryNode* territory)
{
	for (vector<TerritoryNode*>::size_type i=0; i<_adjacentTerritories.size(); i++)
	{
		if (_adjacentTerritories[i]->getName() == territory->getName()) {
			_adjacentTerritories.erase(_adjacentTerritories.begin() + i);
			break;
		}
	}
}

void TerritoryNode::print()
{
	cout << "Territory " << getName();
	cout << " centered at ("<<getX()<<","<<getY()<<"),";
	if (_adjacentTerritories.size() == 0)
	{
		cout << " does not have any adjacent territories";
	}
	else
	{
		cout << " is adjacent to the " << _adjacentTerritories.size() << " following territories: ";
		for (vector<TerritoryNode*>::size_type i=0; i<_adjacentTerritories.size(); i++)
		{
			cout << _adjacentTerritories.at(i)->getName();
			if (i+1 != _adjacentTerritories.size())
				cout << ", ";
		}
	}
	cout << "." << endl;
}
