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
	void input(RenderWindow& window, View& hudView, View& uiView, View& mapView, Vector2f resolution, e_tab& tabStatus, Event& event);
	void researchInput(Vector2f mouseGlobalPosition);
	//void tileInput();
	//void noneInput(Vector2f mousePos, e_tab&, bool);
	void zoom(View&, float);
	void hudInput(Vector2f, e_tab&);

public:
	void run();
};