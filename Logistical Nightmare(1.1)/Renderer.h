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

enum class e_tab { UNITS, RESEARCH, PRODUCTION, LOGISTICS, BUILDING, OPTIONS};

class Renderer
{
protected:
	Vector2f m_tilesNums;
	Vector2f m_mapSize;
	Vector2f m_selectedTile;
	Vector2f m_resolution;
	vector<Researchable> infantryRes;
	vector<Researchable> tankRes;
	vector<Researchable> antiTankRes;
	RectangleShape m_hudBackground;
	RectangleShape m_researchBackground;
	RectangleShape m_mapBackground;
	Text m_allegiance1;
	Text m_allegiance2;
	Text m_tabs[6];
	Text m_time;
	TextureHolder textureHolder;
	Sprite m_tabButtons[6];
	Sprite m_tileSprite;
	Font m_font;
	float runTime = 0;
	static const int m_TILE_SIZE = 200;
	static const float m_ZOOM_SENSITIVITY;
	static const float m_TIME_DILATION;
	static const string m_monthStrings[12];
public:
	Renderer();
	//The draw methods for the engine
	void drawToWindow(RenderWindow& window, View& hudView, View& uiView, View& mapView, e_tab& tabs);
	void drawHudToWindow(RenderWindow& window, View& hudView);
	void drawResearchToWindow(RenderWindow& window, View& uiView);
	//void drawFactoryToWindow(RenderWindow&, View&);
	//void drawTileToWindow(RenderWindow&, View&);
	void drawMapToWindow(RenderWindow& window, View& mapView);
	//void drawStorageToWindow(RenderWindow&, View&);
	static string secondsToDateAndTime(float sec);
};