#include "pch.h"
#include "Equipment.h"
#include "Renderer.h"

float Equipment::m_TEXTURE_SCALE;

std::string Equipment::getName() const
{
	return m_name;
}

float Equipment::getArmor() const
{
	return m_armor;
}

float Equipment::getReliability() const
{
	return m_reliability;
}

float Equipment::getProductionCost() const
{
	return m_productionCost;
}

sf::Sprite Equipment::getEquipmentSprite()
{
	return m_equipmentSprite;
}

Equipment::Equipment(std::string name, float armor, float antiArmor, float antiPersonnel, float productionCost, float reliability)
{
	m_name = name;
	m_armor = armor;
	m_antiArmor = antiArmor;
	m_antiPersonnel = antiPersonnel;
	m_productionCost = productionCost;
	m_reliability = reliability;
	m_equipmentSprite.setTexture(TextureHolder::getTexture(m_name));
	m_TEXTURE_SCALE = (Renderer::resolution.x * 0.1 - 2) / m_equipmentSprite.getLocalBounds().width;
	m_equipmentSprite.setScale(m_TEXTURE_SCALE, m_TEXTURE_SCALE);
}

void Equipment::setSpritePosition(sf::Vector2f position)
{
	m_equipmentSprite.setPosition(position);
}
