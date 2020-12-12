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
#include<unordered_map>
#include"Adjustable.h"
#include"Writable.h"

enum class e_tab { UNITS, RESEARCH, PRODUCTION, PRODUCTION_CLICKED, LOGISTICS, BUILDING, OPTIONS};
enum class e_gameStat { RUNNING, PAUSED };
enum class e_views {HUD, MAP, RESEARCH_LEFT, RESEARCH_RIGHT, PRODUCTION, LOGISTICS, BUILDING, OPTIONS};

class Renderer
{
protected:
	sf::Vector2i tilesNums;
	sf::Vector2f mapSize;
	sf::Vector2f selectedTile;
	Adjustable zoomSensitivity;
	Adjustable cameraSensitivity;
	//Writable IPaddress;
	std::vector<Researchable> allResearch;
	std::unordered_map<std::string, int> stringToResIndex;
	sf::RectangleShape hudBackground;
	sf::RectangleShape researchBackgroundLeft;
	sf::RectangleShape researchFrameLeft;
	sf::RectangleShape researchBackgroundRight;
	sf::RectangleShape mapBackground;
	sf::RectangleShape gameSpeedButtonShade;
	sf::RectangleShape optionsBackground;
	sf::Text allegianceText1;
	sf::Text allegianceText2;
	sf::Text tabTexts[6];
	sf::Text timeAndDate;
	TextureHolder textureHolder;
	sf::Sprite speedButtons;
	sf::Sprite tabButtons[6];
	float runTime = 0;
public:
	static sf::Font font;
	static sf::Vector2f resolution;
	static float ZOOM_SENSITIVITY;
	const static float TIME_DILATION;
	static int GAME_SPEED;
	static std::string monthStrings[12];
	static const int TILE_SIZE = 200;
	Renderer();
	//The draw methods for the engine
	void drawToWindow(sf::RenderWindow& window, std::vector<sf::View>& views, e_tab& tabs, std::vector <std::vector <Tile> >& tiles);
	void drawHudToWindow(sf::RenderWindow& window, sf::View& hudView);
	void drawMapToWindow(sf::RenderWindow& window, sf::View& mapView, std::vector <std::vector <Tile> >& tiles);
	void drawResearchLeftToWindow(sf::RenderWindow& window, std::vector<sf::View>& views);
	void drawResearchRightToWindow(sf::RenderWindow& window, std::vector<sf::View>& views);
	// TODO
	void drawOptionsToWindow(sf::RenderWindow& window, sf::View& optionsView);
	void drawProductionToWindow(sf::RenderWindow& window, std::vector<sf::View>& views, std::vector <std::vector <Tile> >& tiles, e_tab& tabs);
	static std::string secondsToDateAndTime(float sec);
};