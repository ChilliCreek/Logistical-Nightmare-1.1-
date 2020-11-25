#pragma once
#include"pch.h"
#include"Unit.h"
#include <SFML/Graphics.hpp>
#include<iostream>
#include<iomanip>
#include<sstream>
#include"Allegiance.h"
#include"Tile.h"
#include"TextureHolder.h"
#include<fstream>
#include"Researchable.h"

using namespace std;
using namespace sf;

enum class e_gameStat { RUNNING, PAUSED };
enum class e_tab{NONE, RESEARCH, TILE, FACTORY, STORAGE};

class Engine 
{
private:
	Vector2f tilesNums;
	Vector2f mapSize;
	Vector2f selectedTile;
	Vector2f resolution;
	vector <Researchable> infantryRes;
	vector <Researchable> tankRes;
	RectangleShape hudBackground;
	RectangleShape researchBackground;
	RectangleShape mapBackground;
	Text allegiance1;
	Text allegiance2;
	Text tabs[6];
	Font font;

	vector <vector <Tile> > saveLoader(vector<Allegiance>& allegiances);
	//add more to equipment setter
	void equipmentStatSetter();

	void input(RenderWindow&, View&, View&, View&, Vector2f, e_tab&, Event&);
	//void researchInput();
	//void tileInput();
	//void noneInput(Vector2f mousePos, e_tab&, bool);
	//zoom in or out from the map
	void zoom(View&, float);
	void hudInput(Vector2f, e_tab&);
	//The draw method for the engine
	void drawToWindow(RenderWindow&, View&, View&, View&, e_tab&);
	void drawHudToWindow(RenderWindow&, View&);
	void drawResearchToWindow(RenderWindow&, View&);
	//void drawFactoryToWindow(RenderWindow&, View&);
	//void drawTileToWindow(RenderWindow&, View&);
	//void drawMapToWindow(RenderWindow&, View&);
	//void drawStorageToWindow(RenderWindow&, View&);

public:
	void run();
	Engine();
};