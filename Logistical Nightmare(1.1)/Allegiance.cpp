#include "pch.h"
#include "Allegiance.h"

void Allegiance::addFactoryNumber()
{
	m_factoryNumber++;
}

void Allegiance::addTile(int x, int y, Tile* tilePointer)
{
	m_tiles[make_pair(x, y)] = tilePointer;
}

bool Allegiance::ifLost()const
{
	if (m_tiles.size() == 0) {
		return true;
	}
	return false;
}

void Allegiance::update(float)
{

}

void Allegiance::setName(string& name)
{
	m_name = name;
}

string Allegiance::getName()const
{
	return m_name;
}
