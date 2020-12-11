#pragma once
#include"TextureHolder.h"

class Equipment 
{
private:
	float m_armor;
	float m_reliability;
	float m_productionCost;
	float m_antiPersonnel;
	float m_antiArmor;
	sf::Sprite m_equipmentSprite;
	std::string m_name;
public:
	static float m_TEXTURE_SCALE;
	std::string getName()const;
	float getArmor()const;
	float getReliability()const;
	float getProductionCost()const;
	sf::Sprite getEquipmentSprite();
	Equipment(std::string name, float armor, float antiArmor, float antiPersonnel, float productionCost, float reliability);
	void setSpritePosition(sf::Vector2f position);
};
