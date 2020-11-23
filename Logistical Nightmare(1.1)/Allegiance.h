#pragma once
#include<string>
#include<vector>
#include<map>
#include"Tile.h"
using namespace std;

class Allegiance
{
private:
	map <pair <int, int>, Tile*> m_tiles;
	string m_name = 0;
	int m_constructionPoints = 0;
	int m_factoryNumber = 0;
	map <string, int> m_equipmentStorage;
public:
	void addFactoryNumber();
	void addTile(int, int, Tile*);
	bool ifLost()const;
	//TODO: update(float)
	void update(float);
	void setName(string&);
	string getName()const;
};