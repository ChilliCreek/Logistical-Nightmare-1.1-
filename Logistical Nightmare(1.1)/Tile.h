#pragma once
#include"Factory.h"

class Tile : public Factory
{
private:
	bool m_hasFactory;
	int m_terrain;
public:
	Tile(int);
	void addFactory();
	int update(float);
};