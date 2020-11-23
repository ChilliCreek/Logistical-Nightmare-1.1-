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

using namespace std;
using namespace sf;

enum class e_gameStat { RUNNING, PAUSED };
enum class e_tab{NONE, RESEARCH, TILE};

class Engine 
{
private:
	vector <vector <Tile> >& saveLoader(Allegiance[2]);
	void input(RenderWindow&, View&, View&, View&, Vector2f, e_tab&);
	void researchInput();
	void tileInput();
	void noneInput();
	void hudInput(Vector2f mousePos, e_tab&);
	void drawToWindow();
public:
	void run();
};