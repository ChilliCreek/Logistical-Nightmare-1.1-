#pragma once
#include"TextureHolder.h"
#include"Equipment.h"
enum class e_researchStatus{RESEARCHED, IN_PROGRESS, NOT_RESEARCHED};

class Researchable
{
private:
	e_researchStatus m_researchStatus;
	const float RESEARCH_TIME;
	Clock* m_researchClock;
	Equipment m_equipment;
	RectangleShape m_equipmentBackground;
public:
	Equipment& getEquipment();
	Researchable(string name, float armor, float antiArmor, float antiPersonnel, float productionCost, float reliability, Vector2f position, float resTime);
	void doResearch();
	void update();
	RectangleShape& getEquipmentBackground();
};
