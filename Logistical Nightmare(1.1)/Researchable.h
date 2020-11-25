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
public:
	Researchable(string, float, float, float, float, float, Vector2f, float);
	void doResearch(e_researchStatus);
	void update();
	Equipment& getEquipment();
};
