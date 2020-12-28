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

void Allegiance::update(float elapsedTime, Tile*** tiles)
{
	for (auto& location : m_tilesLoc) {
		if (tiles[location.x][location.y]->hasFactory()) {
			std::pair <std::string, int> res = tiles[location.x][location.y]->update(elapsedTime);
			if (res.first == "ConstructionPoints") {
				m_constructionPoints += res.second;
			}
			else {
				m_equipmentStorage[res.first] += res.second;
			}
		}
	}
}

void Allegiance::setName(const std::string& name)
{
	m_name = name;
}

void Allegiance::setConstructionPoints(float constructionPt)
{
	m_constructionPoints = constructionPt;
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
