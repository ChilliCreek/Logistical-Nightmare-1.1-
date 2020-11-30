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

enum class e_gameStat { RUNNING, PAUSED };

class Engine : public Renderer
{
private:
	std::vector <std::vector <Tile> > saveLoader(std::vector<Allegiance>& allegiances);
	void equipmentStatSetter();
	void input(sf::RenderWindow& window, sf::View& hudView, sf::View& uiView, sf::View& mapView, sf::Vector2f resolution, e_tab& tabStatus, sf::Event& event);
	void researchInput(sf::Vector2f mouseGlobalPosition);
	//void tileInput();
	//void noneInput(Vector2f mousePos, e_tab&, bool);
	void zoom(sf::View&, float);
	void hudInput(sf::Vector2f, e_tab&);

public:
	void run();
};