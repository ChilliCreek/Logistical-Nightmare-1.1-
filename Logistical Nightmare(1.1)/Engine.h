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
private:
	static float MAX_ZOOM, MIN_ZOOM;
	static float ZOOM_FACTOR;
	static float CAMERA_SENSITIVITY;
	std::vector <std::vector <Tile> > saveLoader(std::vector<Allegiance>& allegiances);
	void equipmentStatSetter();
	//Any mouse and keyboard that SFML support will work with this method.
	void input(sf::RenderWindow& window, std::vector<sf::View>& views, sf::Vector2f resolution, e_tab& tabStatus, sf::Event& event);
	void researchInput(sf::RenderWindow& window, std::vector<sf::View> views, sf::Vector2i mouseLocalPosition);
	//void tileInput();
	//void noneInput(Vector2f mousePos, e_tab&, bool);
	void zoom(sf::View& mapView, float scrollDelta);
	void hudInput(sf::Vector2f, e_tab&);
public:
	void run();
};