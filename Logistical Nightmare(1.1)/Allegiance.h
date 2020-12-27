#pragma once
#include<string>
#include<vector>
#include<map>
#include<SFML/System/Vector2.hpp>
#include"Tile.h"

class Allegiance
{
private:
	std::vector <sf::Vector2i> m_tilesLoc;
	std::string m_name;
	float m_constructionPoints;
	int m_factoryNumber;
	std::map <std::string, int> m_equipmentStorage;
public:
	void addFactoryNumber();
	void addTile(sf::Vector2i tileLocation);
	bool ifLost()const;
	void update(float elapsedTime, Tile*** tiles);
	void setName(const std::string&);
	float getConstructionPoints();
	void setConstructionPoints(float constructionPt);
	std::string getName()const;
	Allegiance();
};