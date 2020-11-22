#include "pch.h"
#include "Allegiance.h"

void Allegiance::addFactoryNumber()
{
	m_factoryNumber++;
}

void Allegiance::addTile(int x, int y)
{
	m_tiles.push_back(make_pair(x, y));
}

bool Allegiance::ifLost()
{
	if (m_tiles.size() == 0) {
		return true;
	}
	return false;
}

void Allegiance::setName(string& name)
{
	m_name = name;
}

string Allegiance::getName()const
{
	return m_name;
}
