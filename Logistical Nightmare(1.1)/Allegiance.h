#pragma once
#include<string>
#include<vector>
#include<map>
#include<SFML/System/Vector2.hpp>
#include"Tile.h"

using namespace std;


class Allegiance
{
private:
	vector <sf::Vector2i> m_tilesLoc;
	string m_name;
	float m_constructionPoints = 0;
	int m_factoryNumber = 0;
	map <string, int> m_equipmentStorage;
public:
	void addFactoryNumber();
	void addTile(sf::Vector2i tileLocation);
	bool ifLost()const;
	void update(float elapsedTime, vector <vector <Tile> >& tiles);
	void setName(string&);
	float getConstructionPoints()const;
	string getName()const;
	Allegiance();
};