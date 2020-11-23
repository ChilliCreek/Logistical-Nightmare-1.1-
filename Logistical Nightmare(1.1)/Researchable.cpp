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
Researchable::Researchable(string name, Vector2f position, float resTime) : m_researchSprite(TextureHolder::getTexture(name)), RESEARCH_TIME(resTime) {
	m_researchSprite.setPosition(position);
	m_researchStatus = e_researchStatus::NOT_RESEARCHED;
}