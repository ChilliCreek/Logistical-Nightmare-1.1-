#pragma once
#include"pch.h"
#include<string>
#include"Transportable.h"
#include<unordered_map>
#include<queue>
#include<Adjustable.h>
#include<Writable.h>

class Tile
{
public:
	Tile(int terrain, sf::Vector2i pos, int playerNum);
	bool hasFactory()const;
	void addFactory();
	void setEquipmentInProduction(const std::string& equipmentName, float productionCost);
	std::pair <std::string, int> update(int elapsedHours);
	static std::string terrainNumToString(int terrain);
	void drawItselfOnMap(sf::RenderWindow& window, sf::View& view);
	void drawItselfOnProduction(sf::RenderWindow& window, sf::View& view);
	void drawItselfOnLogistics(sf::RenderWindow& window, sf::View& view);
	sf::Sprite& getBeingProduced();
	void initializeTransportable();
	//void launchTransportable();
	inline const std::string& getSelectedEquipment() {
		return m_selectedEquipment;
	}
	inline void setSelectedEquipment(const std::string& equipment) {
		m_selectedEquipment = equipment;
	}
	inline std::unordered_map <std::string, int>& getStorage() {
		return m_storage;
	}
	inline Adjustable& getAdjustable() {
		return m_equipmentNumSelector;
	}
	inline void setEquipmentNumSelected(int equipmentNumSelected) {
		m_equipmentNumSelected = equipmentNumSelected;
		m_equipmentNumSelector.setValues(0, m_storage[m_selectedEquipment], m_equipmentNumSelected);
	}
private:
	TransportablePointer m_inLoadingBay;
	sf::RectangleShape m_tileRec;
	sf::Sprite m_factorySprite;
	sf::Sprite m_terrainSprite;
	sf::Sprite m_beingProduced;
	sf::RectangleShape m_equipmentBackground;
	bool m_hasFactory;
	int m_terrain;
	int m_transportCapacity = 100;
	int m_equipmentNumSelected = 0;
	int m_playerNum;
	float m_factoryOutput = 60.f;
	float m_productionCost = 60.f;
	float m_produced = 0;
	int m_producedBefore = 0;
	std::string m_inProduction;
	std::string m_selectedEquipment = "None";
	Adjustable m_equipmentNumSelector;
	Writable m_priorityGetter;
	std::priority_queue<TransportablePointer, std::vector<TransportablePointer>, TransportablePointerCompare> gg(TransportablePointerCompare);
	std::unordered_map <std::string, int> m_storage;
};