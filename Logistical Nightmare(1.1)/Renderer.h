#pragma once
#include"pch.h"
#include<iostream>
#include"Allegiance.h"
#include"Tile.h"
#include"TextureHolder.h"
#include<fstream>
#include"Researchable.h"
#include"Transportable.h"
#include"Writable.h"
#include "Functions.h"

constexpr float PI = 3.141592f;
constexpr float TIME_RATIO = 1.f / 2.43333333f;


enum class e_tab { UNITS, RESEARCH, PRODUCTION, PRODUCTION_CLICKED, LOGISTICS, LOGISTICS_SEND, BUILDING, OPTIONS};
enum e_gameStat { RUNNING, PAUSED };
enum e_views {HUD, MAP, RESEARCH_LEFT, RESEARCH_RIGHT, PRODUCTION, LOGISTICS, BUILDING, OPTIONS, EQUIPMENT};

class Renderer
{
public:
	static int playerNum;
	static sf::Font font;
	static sf::Vector2f resolution;
	static float ZOOM_SENSITIVITY;
	static int GAME_SPEED;
	static std::string monthStrings[12];
	static const int TILE_SIZE = 200;
	Renderer();
	//The draw methods for the engine
	void drawToWindow(sf::RenderWindow& window, std::vector<std::shared_ptr<sf::View>>& views, e_tab& tabs, Tile*** tiles);
	void drawHudToWindow(sf::RenderWindow& window, std::shared_ptr<sf::View> hudView);
	void drawMapToWindow(sf::RenderWindow& window, std::shared_ptr<sf::View> mapView, Tile*** tiles);
	void drawResearchLeftToWindow(sf::RenderWindow& window, std::vector<std::shared_ptr<sf::View>>& views);
	void drawResearchRightToWindow(sf::RenderWindow& window, std::vector<std::shared_ptr<sf::View>>& views);
	void drawLogisticsToWindow(sf::RenderWindow& window, std::vector<std::shared_ptr<sf::View>>& views, e_tab& tabs, Tile*** tiles);
	// TODO
	void drawOptionsToWindow(sf::RenderWindow& window, std::shared_ptr<sf::View> optionsView);
	void drawProductionToWindow(sf::RenderWindow& window, std::vector<std::shared_ptr<sf::View>>& views, Tile*** tiles, e_tab& tabs);
	static std::string hoursToDateAndTime(int hours);
	inline sf::Vector2i withinMapBounds(sf::Vector2i inp) {
		if (inp.x >= 0 && inp.x < tilesNums.x && inp.y >= 0 && inp.y < tilesNums.y) {
			return inp;
		}
		else {
			return sf::Vector2i(-1, -1);
		}
	}
protected:
	sf::Vector2i selectedLogisticsTile;
	sf::Vector2i tilesNums;
	sf::Vector2f mapSize;
	sf::Vector2f selectedTile;
	Adjustable zoomSensitivity;
	Adjustable cameraSensitivity;
	std::vector <Allegiance> allegiances;
	std::vector<Researchable> allResearch;
	std::unordered_map<std::string, int> stringToResIndex;
	sf::RectangleShape hudBackground;
	sf::RectangleShape researchBackgroundLeft;
	sf::RectangleShape researchFrameLeft;
	sf::RectangleShape researchBackgroundRight;
	sf::RectangleShape mapBackground;
	sf::RectangleShape gameSpeedButtonShade;
	sf::RectangleShape optionsBackground;
	sf::RectangleShape sendButtonBackground;
	sf::RectangleShape exitButton;
	//Logistics button
	sf::Text sendButton;
	sf::Text allegianceText1;
	sf::Text allegianceText2;
	sf::Text tabTexts[6];
	sf::Text timeAndDate;
	TextureHolder textureHolder;
	sf::Sprite speedButtons;
	sf::Sprite tabButtons[6];
	int hours = 4152;
};