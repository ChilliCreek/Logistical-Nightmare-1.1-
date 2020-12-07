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

void Allegiance::update(float elapsedTime, std::vector <std::vector <Tile> >& tiles)
{
	for (auto& location : m_tilesLoc) {
		if (tiles[location.x][location.y].hasFactory()) {
			std::pair <std::string, int> res = tiles[location.x][location.y].update(elapsedTime);
			if (res.first == "ConstructionPoints") {
				m_constructionPoints += res.second;
			}
			else {
				m_equipmentStorage[res.first] += res.second;
			}
		}
	}
	m_constructionPoints += elapsedTime;
}

void Allegiance::setName(std::string& name)
{
	m_name = name;
}

float Allegiance::getConstructionPoints() const
{
	return m_constructionPoints;
}

std::string Allegiance::getName()const
{
	return m_name;
}

Allegiance::Allegiance()
{
	m_factoryNumber = 0;
	m_constructionPoints = 0;
}
