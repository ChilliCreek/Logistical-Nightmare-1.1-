#pragma once
#include"Factory.h"

class Tile : public Factory
{
private:
	string m_allegiance;
	bool m_hasFactory;
	int m_terrain;
public:
	Tile(int, string);
	void addFactory();
	int update(float);
};