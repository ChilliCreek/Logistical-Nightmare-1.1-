#include"pch.h"
#include"Tile.h"
#include<iostream>
Tile::Tile(int terrain)
{
	m_terrain = terrain;
	m_hasFactory = false;
	m_equipmentInProduction = "graphics/kar98k.png";
}

bool Tile::hasFactory() const
{
	return m_hasFactory;
}

void Tile::addFactory()
{
	m_hasFactory = true;
	m_productionCost = 5.f;
}

void Tile::setEquipmentInProduction(std::string equipmentName, float productionCost)
{
	m_productionCost = productionCost;
	m_equipmentInProduction = equipmentName;
}

std::pair <std::string, int> Tile::update(float time)
{
	m_produced += time * (m_factoryOutput / m_productionCost);
	int latestBatch = int(m_produced) - m_producedBefore;
	m_producedBefore = int(m_produced);
	std::pair<std::string, int> result = make_pair(m_equipmentInProduction, latestBatch);
	return result;
}
