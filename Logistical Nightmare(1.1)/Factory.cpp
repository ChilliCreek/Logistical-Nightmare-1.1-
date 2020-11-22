#include "pch.h"
#include "Factory.h"

string Factory::getEquipmentName()const
{
	return m_equipmentName;
}

int Factory::produce(float time)
{
	return m_factoryOutput / m_productionCost * time;
}

void Factory::setEquipment(string& equipmentName)
{
	m_equipmentName = equipmentName;
	m_productionCost = productionCostMap[equipmentName];
}

