#include "pch.h"
#include "Researchable.h"
#include "Renderer.h"
#include<iostream>

int Researchable::researchesInProgress = 0;

void Researchable::doResearch()
{
	if(m_researchStatus == e_researchStatus::NOT_RESEARCHED && researchesInProgress < 3){
		researchesInProgress++;
		m_researchStatus = e_researchStatus::IN_PROGRESS;
		m_equipmentBackground.setOutlineColor(sf::Color::Yellow);
    }
}
void Researchable::update(int hours)
{
	m_resHoursCount += hours;
	if (m_resHoursCount > m_RESEARCH_HOURS) {
		researchesInProgress--;
		m_researchStatus = e_researchStatus::RESEARCHED;
		m_equipmentBackground.setOutlineColor(sf::Color::Green);  
	}
	else {
		m_progressBarLeft.setSize(sf::Vector2f(m_progressBarFull.getLocalBounds().width * m_resHoursCount / m_RESEARCH_HOURS, 10.f));
	}
}
e_researchStatus& Researchable::isResearched()
{
	return m_researchStatus;
}
Equipment& Researchable::getEquipment()
{
	return m_equipment;
}
Researchable::Researchable(std::string name, float armor, float antiArmor, float antiPersonnel, float productionCost, float reliability, sf::Vector2f position, int resHours, int prevRes) : m_RESEARCH_HOURS(resHours), m_equipment(name, armor, antiArmor, antiPersonnel, productionCost, reliability) {
	prevResearchVectorLocation = prevRes;
	m_equipmentBackground.setFillColor(sf::Color::White);
	m_equipmentBackground.setOutlineThickness(-3.f);
	m_equipmentBackground.setOutlineColor(sf::Color::Red);
	m_equipmentBackground.setSize(sf::Vector2f(m_equipment.getEquipmentSprite().getLocalBounds().width * Equipment::m_TEXTURE_SCALE, m_equipment.getEquipmentSprite().getLocalBounds().height * Equipment::m_TEXTURE_SCALE));
	m_equipmentBackground.setPosition(position);
	m_researchStatus = e_researchStatus::NOT_RESEARCHED;
	m_equipment.setSpritePosition(position);
	m_resTimeDays.setString(std::to_string(resHours / 24) + " days" );
	m_resTimeDays.setPosition(position.x + 4, position.y + 2);
	m_resTimeDays.setCharacterSize(13);
	m_resTimeDays.setFillColor(sf::Color::Black);
	m_resTimeDays.setFont(Renderer::font);
	m_progressBarFull.setSize(sf::Vector2f(m_equipmentBackground.getLocalBounds().width, 10.f));
	m_progressBarFull.setFillColor(sf::Color::Red);
	m_progressBarFull.setOutlineColor(sf::Color::Black);
	m_progressBarFull.setOutlineThickness(-1);
	m_progressBarLeft.setSize(sf::Vector2f(m_equipmentBackground.getLocalBounds().width, 10.f));
	m_progressBarLeft.setFillColor(sf::Color::Green);
	m_progressBarLeft.setOutlineColor(sf::Color::Black);
	m_progressBarLeft.setOutlineThickness(-1);
}

sf::RectangleShape Researchable::getEquipmentBackground(){
	return m_equipmentBackground;
}

sf::RectangleShape Researchable::getProgressBarFull()
{
	return m_progressBarFull;
}

sf::RectangleShape Researchable::getProgressBarLeft()
{
	return m_progressBarLeft;
}

sf::Text& Researchable::getResTimeText()
{
	return m_resTimeDays;
}
