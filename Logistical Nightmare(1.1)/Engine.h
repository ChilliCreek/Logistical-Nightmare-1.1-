#pragma once
#include"pch.h"
#include<fstream>
#include<cmath>
#include"Renderer.h"
#include"Allegiance.h"
#include"Tile.h"
#include"TextureHolder.h"
#include"Researchable.h"

//To make code in Engine class less, created Renderer class to separate the draw/render part of the Engine. Engine is-a Renderer.
class Engine : public Renderer
{
public:
	void run();
private:
	sf::Event event;
	Tile*** saveLoader(std::vector<Allegiance>& allegiances);
	void equipmentStatSetter();
	/*!
	 * @brief Handles time in the game engine.
	 * @param (int) hours Updates the parameters to the total number of "game" hours that passed since the execution of the game loop
	 * @param (float) The number of seconds that has passed in real time. 
	 * @return (int) How many "game" hours have passed since the last time the function.
	 */
	int handleTime(int& hours, float sec);
	void input(sf::RenderWindow& window, std::vector<sf::View>& views, sf::Vector2f resolution, e_tab& tabStatus, Tile*** tiles);
	void hudInput(sf::Vector2f, e_tab&);
	void researchInput(sf::RenderWindow& window, std::vector<sf::View>& views, sf::Vector2i mouseLocalPosition);
	void productionInput(sf::RenderWindow& window, std::vector<sf::View>& views, sf::Vector2i mouseLocalPosition, e_tab& tabStatus, Tile*** tiles);
	void logisticsInput(sf::RenderWindow& window, std::vector<sf::View>& views, sf::Vector2i mouseLocalPosition, Tile*** tiles, e_tab tabStatus);
	void optionsInput(sf::Vector2f mouseGlobalPos);
	void zoom(sf::View& mapView, float scrollDelta, float& zoomFactor);
	void cameraMover(sf::View& view, sf::Vector2f boundsMax, sf::Vector2f boundsMin);
	static float MAX_ZOOM, MIN_ZOOM;
	static float ZOOM_FACTOR_MAP;
	static float ZOOM_FACTOR_PRODUCTION;
	static float CAMERA_SENSITIVITY;
	sf::Vector2i productionSelectedTile;
};       