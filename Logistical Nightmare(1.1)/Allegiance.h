#pragma once
#include<string>
#include<vector>
#include<map>
#include"Tile.h"
using namespace std;

class Allegiance
{
private:
	vector <pair <int, int> > m_tiles;
	string m_name = 0;
	int m_constructionPoints;
	int m_factoryNumber = 0;
	map <string, int> m_equipmentStorage;
public:
	void addFactoryNumber();
	void addTile(int, int);
	bool ifLost();
	void update(vector <vector <Tile> >&, float);
	void setName(string&);
	string getName()const;
};