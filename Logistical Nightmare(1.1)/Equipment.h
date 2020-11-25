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
	string getName()const;
	float getArmor()const;
	float getReliability()const;
	float getProductionCost()const;
	Sprite& getEquipmentSprite();
	Equipment(string, float, float, float, float, float);
	void setSpritePosition(Vector2f);
};