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
enum class e_gameStat { RUNNING, PAUSED };
enum class e_views {HUD, MAP, RESEARCH_LEFT, RESEARCH_RIGHT, PRODUCTION, LOGISTICS, BUILDING, OPTIONS};

class Renderer
{
protected:
	sf::Vector2i tilesNums;
	sf::Vector2f mapSize;
	sf::Vector2f selectedTile;
	std::vector<Researchable> allResearch;
	sf::RectangleShape hudBackground;
	sf::RectangleShape researchBackgroundLeft;
	sf::RectangleShape researchFrameLeft;
	sf::RectangleShape researchBackgroundRight;
	sf::RectangleShape mapBackground;
	sf::Text allegiance1;
	sf::Text allegiance2;
	sf::Text tabTexts[6];
	sf::Text timeAndDate;
	TextureHolder textureHolder;
	sf::Sprite tabButtons[6];
	float runTime = 0;
public:
	static sf::Font font;
	static sf::Vector2f resolution;
	static float ZOOM_SENSITIVITY;
	static float TIME_DILATION;
	static std::string monthStrings[12];
	static const int TILE_SIZE = 200;
	Renderer();
	//The draw methods for the engine
	void drawToWindow(sf::RenderWindow& window, std::vector<sf::View>& views, e_tab& tabs, std::vector <std::vector <Tile> >& tiles);
	void drawHudToWindow(sf::RenderWindow& window, sf::View& hudView);
	void drawMapToWindow(sf::RenderWindow& window, sf::View& mapView, std::vector <std::vector <Tile> >& tiles);
	void drawResearchToWindow(sf::RenderWindow& window, std::vector<sf::View>& views);
	static std::string secondsToDateAndTime(float sec);
};