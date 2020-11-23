#include "pch.h"
#include "Tile.h"

Tile::Tile(int terrain)
{
	m_terrain = terrain;
	m_hasFactory = false;
}

void Tile::addFactory()
{
	m_hasFactory = true;
}

int Tile::update(float time)
{
	if (m_hasFactory) {
		return produce(time);
	}
	else {
		return 0;
	}
}
