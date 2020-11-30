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
	Sprite m_equipmentSprite;
	string m_name;
public:
	static const float m_TEXTURE_SCALE;
	string getName()const;
	float getArmor()const;
	float getReliability()const;
	float getProductionCost()const;
	Sprite& getEquipmentSprite();
	Equipment(string name, float armor, float antiArmor, float antiPersonnel, float productionCost, float reliability);
	void setSpritePosition(Vector2f position);
};