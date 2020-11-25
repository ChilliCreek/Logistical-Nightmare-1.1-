#include "pch.h"
#include "Researchable.h"

void Researchable::doResearch(e_researchStatus)
{
	m_researchClock = new Clock();
	m_researchClock->restart();
	m_researchStatus = e_researchStatus::IN_PROGRESS;
}
void Researchable::update()
{
	if (m_researchClock != nullptr && m_researchClock->getElapsedTime().asSeconds() > RESEARCH_TIME) {
		delete[] m_researchClock;
		m_researchClock = nullptr;
		m_researchStatus = e_researchStatus::RESEARCHED;
	}
}
Equipment& Researchable::getEquipment()
{
	return m_equipment;
}
Researchable::Researchable(string name, float armor, float antiArmor, float antiPersonnel, float productionCost, float reliability, Vector2f position, float resTime) : RESEARCH_TIME(resTime), m_equipment(name, armor, antiArmor, antiPersonnel, productionCost, reliability) {
	m_researchStatus = e_researchStatus::NOT_RESEARCHED;
	m_equipment.setSpritePosition(position);
}