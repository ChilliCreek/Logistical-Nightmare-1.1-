#pragma once
#include<string>
#include<vector>
#include<map>
#include<SFML/System/Vector2.hpp>
#include"Tile.h"

class Allegiance
{
public:
	void addFactoryNumber();
	void addTile(sf::Vector2i tileLocation);
	bool ifLost()const;
	void update(int elapsedHours, Tile*** tiles);
	void setName(const std::string&);
	inline float getConstructionPoints() {
		return m_constructionPoints;
	}
	void setConstructionPoints(float constructionPt);
	inline std::map <std::string, int>& getEquipmentStorage() {
		return m_equipmentStorage;
	}
	std::string getName()const;
	Allegiance();
private:
	std::vector <sf::Vector2i> m_tilesLoc;
	std::string m_name;
	float m_constructionPoints;
	int m_factoryNumber;
	std::map <std::string, int> m_equipmentStorage;
};