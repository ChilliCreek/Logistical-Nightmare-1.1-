#include "pch.h"
#include "Researchable.h"
#include<iostream>

void Researchable::doResearch()
{
	if(m_researchStatus == e_researchStatus::NOT_RESEARCHED){
		m_researchClock = new sf::Clock();
		m_researchClock->restart();
		m_researchStatus = e_researchStatus::IN_PROGRESS;
		m_equipmentBackground.setOutlineColor(sf::Color::Yellow);
    }
}
void Researchable::update()
{
	if (m_researchClock != nullptr && m_researchClock->getElapsedTime().asSeconds() > RESEARCH_TIME) {
		std::cout << m_researchClock->getElapsedTime().asSeconds();
		delete[] m_researchClock;
		m_researchClock = nullptr;
		m_researchStatus = e_researchStatus::RESEARCHED;
		m_equipmentBackground.setOutlineColor(sf::Color::Green);
	}
}
Equipment& Researchable::getEquipment()
{
	return m_equipment;
}
Researchable::Researchable(std::string name, float armor, float antiArmor, float antiPersonnel, float productionCost, float reliability, sf::Vector2f position, float resTime) : RESEARCH_TIME(resTime), m_equipment(name, armor, antiArmor, antiPersonnel, productionCost, reliability) {
	m_equipmentBackground.setFillColor(sf::Color::White);
	m_equipmentBackground.setOutlineThickness(-3.f);
	m_equipmentBackground.setOutlineColor(sf::Color::Red);
	m_equipmentBackground.setSize(sf::Vector2f(m_equipment.getEquipmentSprite().getLocalBounds().width * Equipment::m_TEXTURE_SCALE, m_equipment.getEquipmentSprite().getLocalBounds().height * Equipment::m_TEXTURE_SCALE));
	m_equipmentBackground.setPosition(position);
	m_researchStatus = e_researchStatus::NOT_RESEARCHED;
	m_equipment.setSpritePosition(position);
	m_researchClock = nullptr;
}

sf::RectangleShape& Researchable::getEquipmentBackground(){
	return m_equipmentBackground;
}