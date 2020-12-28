#pragma once
#include"pch.h"
#include<string>
#include<utility>
#include"Transportable.h"
#include<unordered_map>

class Tile
{
public:
	Tile(int terrain, sf::Vector2i pos);
	bool hasFactory()const;
	void addFactory();
	void setEquipmentInProduction(const std::string& equipmentName, float productionCost);
	std::pair <std::string, int> update(float);
	static std::string terrainNumToString(int terrain);
	void drawItselfOnMap(sf::RenderWindow& window, sf::View& view);
	void drawItselfOnProduction(sf::RenderWindow& window, sf::View& view);
	sf::Sprite& getBeingProduced();
private:
	sf::RectangleShape m_tileRec;
	sf::Sprite m_factorySprite;
	sf::Sprite m_terrainSprite;
	sf::Sprite m_beingProduced;
	bool m_hasFactory;
	int m_terrain;
	float m_factoryOutput = 100.f;
	float m_productionCost = 50.f;
	float m_produced = 0;
	int m_producedBefore = 0;
	std::string m_inProduction;
	std::priority_queue<Transportable, std::vector<Transportable>, Compare> gg(Compare);
	std::unordered_map <std::string, int> m_storage;
};