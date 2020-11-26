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
#include"Renderer.h"

using namespace std;
using namespace sf;

enum class e_gameStat { RUNNING, PAUSED };

class Engine : public Renderer
{
private:
	vector <vector <Tile> > saveLoader(vector<Allegiance>& allegiances);
	void equipmentStatSetter();
	void input(RenderWindow&, View&, View&, View&, Vector2f, e_tab&, Event&);
	//void researchInput();
	//void tileInput();
	//void noneInput(Vector2f mousePos, e_tab&, bool);
	void zoom(View&, float);
	void hudInput(Vector2f, e_tab&);

public:
	void run();
	//Engine();
};