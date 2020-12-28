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

//To make code in Engine class less, created Renderer class to separate the draw/render part of the Engine. Engine is-a Renderer.
class Engine : public Renderer
{
public:
	void run();
private:
	Tile*** saveLoader(std::vector<Allegiance>& allegiances);
	void equipmentStatSetter();
	void input(sf::RenderWindow& window, std::vector<sf::View>& views, sf::Vector2f resolution, e_tab& tabStatus, sf::Event& event, Tile*** tiles);
	void hudInput(sf::Vector2f, e_tab&);
	void researchInput(sf::RenderWindow& window, std::vector<sf::View>& views, sf::Vector2i mouseLocalPosition);
	void productionInput(sf::RenderWindow& window, std::vector<sf::View>& views, sf::Vector2i mouseLocalPosition, e_tab& tabStatus, Tile*** tiles);
	void optionsInput(sf::Vector2f mouseGlobalPos);
	void zoom(sf::View& mapView, float scrollDelta, float& zoomFactor);
	void cameraMover(sf::View& view, sf::Vector2f boundsMax, sf::Vector2f boundsMin);
	static float MAX_ZOOM, MIN_ZOOM;
	static float ZOOM_FACTOR_MAP;
	static float ZOOM_FACTOR_PRODUCTION;
	static float CAMERA_SENSITIVITY;
	sf::Vector2i productionSelectedTile;
};