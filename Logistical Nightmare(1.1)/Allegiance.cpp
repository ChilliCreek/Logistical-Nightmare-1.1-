#include "pch.h"
#include "Allegiance.h"

void Allegiance::addFactoryNumber()
{
	m_factoryNumber++;
}

void Allegiance::addTile(sf::Vector2i tileLocation)
{
	m_tilesLoc.push_back(tileLocation);
}

bool Allegiance::ifLost()const
{
	if (m_tilesLoc.size() == 0) {
		return true;
	}
	return false;
}

void Allegiance::update(float elapsedTime, vector <vector <Tile> >& tiles)
{
	for (auto& location : m_tilesLoc) {
		if (tiles[location.x][location.y].hasFactory()) {
			pair <string, int> res = tiles[location.x][location.y].update(elapsedTime);
			m_equipmentStorage[res.first] += res.second;
		}
	}
	m_constructionPoints += elapsedTime;
}

void Allegiance::setName(string& name)
{
	m_name = name;
}

float Allegiance::getConstructionPoints() const
{
	return m_constructionPoints;
}

string Allegiance::getName()const
{
	return m_name;
}

Allegiance::Allegiance()
{
}
