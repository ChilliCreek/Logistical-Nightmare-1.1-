#include "pch.h"
#include "Equipment.h"

string Equipment::getName() const
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

Sprite& Equipment::getEquipmentSprite()
{
	return m_equipmentSprite;
}

Equipment::Equipment(string name, float armor, float antiArmor, float antiPersonnel, float productionCost, float reliability)
{
	m_name = name;
	m_armor = armor;
	m_antiArmor = antiArmor;
	m_antiPersonnel = antiPersonnel;
	m_productionCost = productionCost;
	m_reliability = reliability;
	m_equipmentSprite.setTexture(TextureHolder::getTexture(m_name));
	m_equipmentSprite.setScale(0.25, 0.25);
}

void Equipment::setSpritePosition(Vector2f position)
{
	m_equipmentSprite.setPosition(position);
}
