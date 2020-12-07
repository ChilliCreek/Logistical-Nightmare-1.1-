#pragma once
#include"TextureHolder.h"
#include"Equipment.h"
enum class e_researchStatus{RESEARCHED, IN_PROGRESS, NOT_RESEARCHED};

class Researchable
{
private:
	e_researchStatus m_researchStatus;
	sf::Text m_resTimeDays;
	const float m_RESEARCH_TIME_SEC;
	sf::Clock* m_researchClock;
	Equipment m_equipment;
	sf::RectangleShape m_equipmentBackground;
	sf::RectangleShape m_progressBarFull;
	sf::RectangleShape m_progressBarLeft;
public:
	static int researchesInProgress;
	int prevResearchVectorLocation = -1;
	Equipment& getEquipment();
	Researchable(std::string name, float armor, float antiArmor, float antiPersonnel, float productionCost, float reliability, sf::Vector2f position, float resTime, int prevRes);
	void doResearch();
	void update();
	e_researchStatus& isResearched();
	sf::RectangleShape getEquipmentBackground();
	sf::RectangleShape getProgressBarFull();
	sf::RectangleShape getProgressBarLeft();
	sf::Text& getResTimeText();
};
