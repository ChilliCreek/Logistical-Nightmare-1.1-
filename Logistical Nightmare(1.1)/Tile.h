#pragma once
#include"pch.h"
#include<string>
#include<utility>

using namespace std;

class Tile
{
private:
	bool m_hasFactory;
	int m_terrain;
	float m_factoryOutput = 100.0;
	float m_productionCost;
	float m_produced = 0;
	int m_producedBefore = 0;
public:
	string m_equipmentInProduction;
	Tile(int terrain);
	bool hasFactory()const;
	void addFactory();
	void setEquipmentInProduction(string equipmentName, float productionCost);
	pair <string, int> update(float);
};