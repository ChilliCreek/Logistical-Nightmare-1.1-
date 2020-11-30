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
	sf::Vector2f m_tilesNums;
	sf::Vector2f m_mapSize;
	sf::Vector2f m_selectedTile;
	sf::Vector2f m_resolution;
	std::vector<Researchable> infantryRes;
	std::vector<Researchable> tankRes;
	std::vector<Researchable> antiTankRes;
	sf::RectangleShape m_hudBackground;
	sf::RectangleShape m_researchBackground;
	sf::RectangleShape m_mapBackground;
	sf::Text m_allegiance1;
	sf::Text m_allegiance2;
	sf::Text m_tabs[6];
	sf::Text m_time;
	TextureHolder textureHolder;
	sf::Sprite m_tabButtons[6];
	sf::Sprite m_tileSprite;
	sf::Font m_font;
	float runTime = 0;
	static const int m_TILE_SIZE = 200;
	static const float m_ZOOM_SENSITIVITY;
	static const float m_TIME_DILATION;
	static const std::string m_monthStrings[12];
public:
	Renderer();
	//The draw methods for the engine
	void drawToWindow(sf::RenderWindow& window, sf::View& hudView, sf::View& uiView, sf::View& mapView, e_tab& tabs);
	void drawHudToWindow(sf::RenderWindow& window, sf::View& hudView);
	void drawResearchToWindow(sf::RenderWindow& window, sf::View& uiView);
	//void drawFactoryToWindow(RenderWindow&, View&);
	//void drawTileToWindow(RenderWindow&, View&);
	void drawMapToWindow(sf::RenderWindow& window, sf::View& mapView);
	//void drawStorageToWindow(RenderWindow&, View&);
	static std::string secondsToDateAndTime(float sec);
};