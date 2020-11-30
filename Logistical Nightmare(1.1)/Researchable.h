#pragma once
#include"TextureHolder.h"
#include"Equipment.h"
enum class e_researchStatus{RESEARCHED, IN_PROGRESS, NOT_RESEARCHED};

class Researchable
{
private:
	e_researchStatus m_researchStatus;
	const float RESEARCH_TIME;
	sf::Clock* m_researchClock;
	Equipment m_equipment;
	sf::RectangleShape m_equipmentBackground;
public:
	Equipment& getEquipment();
	Researchable(std::string name, float armor, float antiArmor, float antiPersonnel, float productionCost, float reliability, sf::Vector2f position, float resTime);
	void doResearch();
	void update();
	sf::RectangleShape& getEquipmentBackground();
};
