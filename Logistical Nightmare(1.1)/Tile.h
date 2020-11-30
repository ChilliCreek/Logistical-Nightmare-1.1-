#pragma once
#include"pch.h"
#include<string>
#include<utility>

class Tile
{
private:
	bool m_hasFactory;
	int m_terrain;
	float m_factoryOutput = 100.0;
	float m_productionCost;
	float m_produced = 0;
	int m_producedBefore = 0;
	std::string m_equipmentInProduction;
public:
	Tile(int terrain);
	bool hasFactory()const;
	void addFactory();
	void setEquipmentInProduction(std::string equipmentName, float productionCost);
	std::pair <std::string, int> update(float);
};