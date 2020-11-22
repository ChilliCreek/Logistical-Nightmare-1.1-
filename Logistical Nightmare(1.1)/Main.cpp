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
using namespace sf;
using namespace std;

enum class gameStat{RUNNING, PAUSED};

vector <vector <Tile> >& initializer(Allegiance allegiance[2]);

int main() {
	Allegiance allegiances[2];
	vector <vector <Tile> >& tiles = initializer(allegiances);

	gameStat gameStatus = gameStat::RUNNING;

	VideoMode vm(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
	RenderWindow window(vm, "Logistical Nightmare", Style::Fullscreen);

	//Background
	Texture textureBackground;
	textureBackground.loadFromFile("graphics/plain.png");
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);

	//Font
	Font font;
	font.loadFromFile("font/KOMIKAP_.ttf");

	//Creating the menu bar
	RectangleShape menuBar;
	menuBar.setFillColor(Color(170, 105, 30));
	menuBar.setSize(Vector2f(1440, 150));

	while (window.isOpen()) {

		if (!Keyboard::isKeyPressed(lastHitBlue) && inputStatusBlue == e_inputStat::PAUSED) {
			inputStatusBlue = e_inputStat::RUNNING;
		}
		if (!Keyboard::isKeyPressed(lastHitRed) && inputStatusRed == e_inputStat::PAUSED) {
			inputStatusRed = e_inputStat::RUNNING;
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		if (inputStatusBlue == e_inputStat::RUNNING) {
			//unit selection
			if (Keyboard::isKeyPressed(Keyboard::Num1)) {
				unitSelection_left = unitType::INF;
				frame_left.setPosition(Vector2f(120, 75));
				inputStatusBlue = e_inputStat::PAUSED;
				lastHitBlue = Keyboard::Num1;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Num2)) {
				unitSelection_left = unitType::AT;
				frame_left.setPosition(Vector2f(360, 75));
				inputStatusBlue = e_inputStat::PAUSED;
				lastHitBlue = Keyboard::Num2;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Num3)) {
				unitSelection_left = unitType::LT;
				frame_left.setPosition(Vector2f(600, 75));
				inputStatusBlue = e_inputStat::PAUSED;
				lastHitBlue = Keyboard::Num3;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Num4)) {
				unitSelection_left = unitType::MT;
				frame_left.setPosition(Vector2f(840, 75));
				inputStatusBlue = e_inputStat::PAUSED;
				lastHitBlue = Keyboard::Num4;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Num5)) {
				unitSelection_left = unitType::HT;
				frame_left.setPosition(Vector2f(1080, 75));
				inputStatusBlue = e_inputStat::PAUSED;
				lastHitBlue = Keyboard::Num5;
			} //Set ready for the turn (left)
			else if (Keyboard::isKeyPressed(Keyboard::Z) && playerStatusBlue == e_playerStat::NOT_READY) {
				playerStatusBlue = e_playerStat::READY;
				inputStatusBlue = e_inputStat::PAUSED;
				lastHitBlue = Keyboard::Z;
			}
			//Unit spawning
			else if (Keyboard::isKeyPressed(Keyboard::Q) && spawnUnitLeft_x == 0 && unitGrid[spawnUnitLeft_x][spawnUnitLeft_y].getType() == unitType::EMPTY) {
				if (unit::typeToNum(unitSelection_left) * 10 + 10 <= factoryOutput0) {
					unitGrid[spawnUnitLeft_x][spawnUnitLeft_y].create(unit::typeToNum(unitSelection_left), true);
					factoryOutput0 -= unit::typeToNum(unitSelection_left) * 10 + 10;
					factoryOutput_Left.setString("Factory Output = " + std::to_string(factoryOutput0));
				}
				inputStatusBlue = e_inputStat::PAUSED;
				lastHitBlue = Keyboard::Q;
			}
			//Movement left side

			else if (Keyboard::isKeyPressed(Keyboard::W) && unitFrame_left.getPosition().y > 210) {
				if (Keyboard::isKeyPressed(Keyboard::LShift) && unitGrid[spawnUnitLeft_x][spawnUnitLeft_y].getMovedOrNot() == false && unitGrid[spawnUnitLeft_x][spawnUnitLeft_y].getType() != unitType::EMPTY) {
					if (unitGrid[spawnUnitLeft_x][spawnUnitLeft_y].getLeftOrNot() == true) {
						if (unitGrid[spawnUnitLeft_x][spawnUnitLeft_y - 1].getLeftOrNot() == true || unitGrid[spawnUnitLeft_x][spawnUnitLeft_y - 1].getType() == unitType::EMPTY)unitGrid[spawnUnitLeft_x][spawnUnitLeft_y].move(unitGrid[spawnUnitLeft_x][spawnUnitLeft_y - 1]);
						else unitGrid[spawnUnitLeft_x][spawnUnitLeft_y].battle(unitGrid[spawnUnitLeft_x][spawnUnitLeft_y - 1]);
					}
				}
				unitFrame_left.setPosition(Vector2f(unitFrame_left.getPosition().x, unitFrame_left.getPosition().y - 120));
				spawnUnitLeft_y--;
				inputStatusBlue = e_inputStat::PAUSED;
				lastHitBlue = Keyboard::W;
			}
			else if (Keyboard::isKeyPressed(Keyboard::A) && unitFrame_left.getPosition().x > 60) {
				if (Keyboard::isKeyPressed(Keyboard::LShift) && unitGrid[spawnUnitLeft_x][spawnUnitLeft_y].getMovedOrNot() == false && unitGrid[spawnUnitLeft_x][spawnUnitLeft_y].getType() != unitType::EMPTY) {
					if (unitGrid[spawnUnitLeft_x][spawnUnitLeft_y].getLeftOrNot() == true) {
						if (unitGrid[spawnUnitLeft_x - 1][spawnUnitLeft_y].getLeftOrNot() == true || unitGrid[spawnUnitLeft_x - 1][spawnUnitLeft_y].getType() == unitType::EMPTY)unitGrid[spawnUnitLeft_x][spawnUnitLeft_y].move(unitGrid[spawnUnitLeft_x - 1][spawnUnitLeft_y]);
						else unitGrid[spawnUnitLeft_x][spawnUnitLeft_y].battle(unitGrid[spawnUnitLeft_x - 1][spawnUnitLeft_y]);
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::LShift)) {
					unitGrid[spawnUnitLeft_x][spawnUnitLeft_y].move(unitGrid[spawnUnitLeft_x - 1][spawnUnitLeft_y]);
				}
				unitFrame_left.setPosition(Vector2f(unitFrame_left.getPosition().x - 120, unitFrame_left.getPosition().y));
				spawnUnitLeft_x--;
				inputStatusBlue = e_inputStat::PAUSED;
				lastHitBlue = Keyboard::A;
			}
			else if (Keyboard::isKeyPressed(Keyboard::S) && unitFrame_left.getPosition().y < 690) {
				if (Keyboard::isKeyPressed(Keyboard::LShift) && unitGrid[spawnUnitLeft_x][spawnUnitLeft_y].getMovedOrNot() == false && unitGrid[spawnUnitLeft_x][spawnUnitLeft_y].getType() != unitType::EMPTY) {
					if (unitGrid[spawnUnitLeft_x][spawnUnitLeft_y].getLeftOrNot() == true) {
						if (unitGrid[spawnUnitLeft_x][spawnUnitLeft_y + 1].getLeftOrNot() == true || unitGrid[spawnUnitLeft_x][spawnUnitLeft_y + 1].getType() == unitType::EMPTY)unitGrid[spawnUnitLeft_x][spawnUnitLeft_y].move(unitGrid[spawnUnitLeft_x][spawnUnitLeft_y + 1]);
						else unitGrid[spawnUnitLeft_x][spawnUnitLeft_y].battle(unitGrid[spawnUnitLeft_x][spawnUnitLeft_y + 1]);
					}
				}
				unitFrame_left.setPosition(Vector2f(unitFrame_left.getPosition().x, unitFrame_left.getPosition().y + 120));
				spawnUnitLeft_y++;
				inputStatusBlue = e_inputStat::PAUSED;
				lastHitBlue = Keyboard::S;
			}
			else if (Keyboard::isKeyPressed(Keyboard::D) && unitFrame_left.getPosition().x < 1380) {
				if (Keyboard::isKeyPressed(Keyboard::LShift) && unitGrid[spawnUnitLeft_x][spawnUnitLeft_y].getMovedOrNot() == false && unitGrid[spawnUnitLeft_x][spawnUnitLeft_y].getType() != unitType::EMPTY) {
					if (unitGrid[spawnUnitLeft_x][spawnUnitLeft_y].getLeftOrNot() == true) {
						if (unitGrid[spawnUnitLeft_x + 1][spawnUnitLeft_y].getLeftOrNot() == true || unitGrid[spawnUnitLeft_x + 1][spawnUnitLeft_y].getType() == unitType::EMPTY)unitGrid[spawnUnitLeft_x][spawnUnitLeft_y].move(unitGrid[spawnUnitLeft_x + 1][spawnUnitLeft_y]);
						else unitGrid[spawnUnitLeft_x][spawnUnitLeft_y].battle(unitGrid[spawnUnitLeft_x + 1][spawnUnitLeft_y]);
					}
				}
				unitFrame_left.setPosition(Vector2f(unitFrame_left.getPosition().x + 120, unitFrame_left.getPosition().y));
				spawnUnitLeft_x++;
				inputStatusBlue = e_inputStat::PAUSED;
				lastHitBlue = Keyboard::D;
			}
		}
		if (inputStatusRed == e_inputStat::RUNNING) {
			if (Keyboard::isKeyPressed(Keyboard::Num6)) {
				unitSelection_right = unitType::HT;
				frame_right.setPosition(Vector2f(360, 825));
				inputStatusRed = e_inputStat::PAUSED;
				lastHitRed = Keyboard::Num6;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Num7)) {
				unitSelection_right = unitType::MT;
				frame_right.setPosition(Vector2f(600, 825));
				inputStatusRed = e_inputStat::PAUSED;
				lastHitRed = Keyboard::Num7;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Num8)) {
				unitSelection_right = unitType::LT;
				frame_right.setPosition(Vector2f(840, 825));
				inputStatusRed = e_inputStat::PAUSED;
				lastHitRed = Keyboard::Num8;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Num9)) {
				unitSelection_right = unitType::AT;
				frame_right.setPosition(Vector2f(1080, 825));
				inputStatusRed = e_inputStat::PAUSED;
				lastHitRed = Keyboard::Num9;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Num0)) {
				unitSelection_right = unitType::INF;
				frame_right.setPosition(Vector2f(1320, 825));
				inputStatusRed = e_inputStat::PAUSED;
				lastHitRed = Keyboard::Num0;
			} // Set ready for the turn (right)
			else if (Keyboard::isKeyPressed(Keyboard::P) && playerStatusRed == e_playerStat::NOT_READY) {
				playerStatusRed = e_playerStat::READY;
				inputStatusRed = e_inputStat::PAUSED;
				lastHitRed = Keyboard::P;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Slash) && spawnUnitRight_x == 11 && unitGrid[spawnUnitRight_x][spawnUnitRight_y].getType() == unitType::EMPTY) {
				if (unit::typeToNum(unitSelection_right) * 10 + 10 <= factoryOutput1) {
					unitGrid[spawnUnitRight_x][spawnUnitRight_y].create(unit::typeToNum(unitSelection_right), false);
					factoryOutput1 -= unit::typeToNum(unitSelection_right) * 10 + 10;
					factoryOutput_Right.setString("Factory Output = " + std::to_string(factoryOutput1));
				}
				inputStatusRed = e_inputStat::PAUSED;
				lastHitRed = Keyboard::Slash;
			}
			//Movement right side

			else if (Keyboard::isKeyPressed(Keyboard::Up) && unitFrame_right.getPosition().y > 210) {
				if (Keyboard::isKeyPressed(Keyboard::RShift) && unitGrid[spawnUnitRight_x][spawnUnitRight_y].getMovedOrNot() == false && unitGrid[spawnUnitRight_x][spawnUnitRight_y].getType() != unitType::EMPTY) {
					if (unitGrid[spawnUnitRight_x][spawnUnitRight_y].getLeftOrNot() == false) {
						if (unitGrid[spawnUnitRight_x][spawnUnitRight_y - 1].getLeftOrNot() == false || unitGrid[spawnUnitRight_x][spawnUnitRight_y - 1].getType() == unitType::EMPTY)unitGrid[spawnUnitRight_x][spawnUnitRight_y].move(unitGrid[spawnUnitRight_x][spawnUnitRight_y - 1]);
						else unitGrid[spawnUnitRight_x][spawnUnitRight_y].battle(unitGrid[spawnUnitRight_x][spawnUnitRight_y - 1]);
					}
				}
				unitFrame_right.setPosition(Vector2f(unitFrame_right.getPosition().x, unitFrame_right.getPosition().y - 120));
				spawnUnitRight_y--;
				inputStatusRed = e_inputStat::PAUSED;
				lastHitRed = Keyboard::Up;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Left) && unitFrame_right.getPosition().x > 60) {
				if (Keyboard::isKeyPressed(Keyboard::RShift) && unitGrid[spawnUnitRight_x][spawnUnitRight_y].getMovedOrNot() == false && unitGrid[spawnUnitRight_x][spawnUnitRight_y].getType() != unitType::EMPTY) {
					if (unitGrid[spawnUnitRight_x][spawnUnitRight_y].getLeftOrNot() == false) {
						if (unitGrid[spawnUnitRight_x - 1][spawnUnitRight_y].getLeftOrNot() == false || unitGrid[spawnUnitRight_x - 1][spawnUnitRight_y].getType() == unitType::EMPTY)unitGrid[spawnUnitRight_x][spawnUnitRight_y].move(unitGrid[spawnUnitRight_x - 1][spawnUnitRight_y]);
						else unitGrid[spawnUnitRight_x][spawnUnitRight_y].battle(unitGrid[spawnUnitRight_x - 1][spawnUnitRight_y]);
					}
				}
				unitFrame_right.setPosition(Vector2f(unitFrame_right.getPosition().x - 120, unitFrame_right.getPosition().y));
				spawnUnitRight_x--;
				inputStatusRed = e_inputStat::PAUSED;
				lastHitRed = Keyboard::Left;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Down) && unitFrame_right.getPosition().y < 690) {
				if (Keyboard::isKeyPressed(Keyboard::RShift) && unitGrid[spawnUnitRight_x][spawnUnitRight_y].getMovedOrNot() == false && unitGrid[spawnUnitRight_x][spawnUnitRight_y].getType() != unitType::EMPTY) {
					if (unitGrid[spawnUnitRight_x][spawnUnitRight_y].getLeftOrNot() == false) {
						if (unitGrid[spawnUnitRight_x][spawnUnitRight_y + 1].getLeftOrNot() == false || unitGrid[spawnUnitRight_x][spawnUnitRight_y + 1].getType() == unitType::EMPTY)unitGrid[spawnUnitRight_x][spawnUnitRight_y].move(unitGrid[spawnUnitRight_x][spawnUnitRight_y + 1]);
						else unitGrid[spawnUnitRight_x][spawnUnitRight_y].battle(unitGrid[spawnUnitRight_x][spawnUnitRight_y + 1]);
					}
				}
				unitFrame_right.setPosition(Vector2f(unitFrame_right.getPosition().x, unitFrame_right.getPosition().y + 120));
				spawnUnitRight_y++;
				inputStatusRed = e_inputStat::PAUSED;
				lastHitRed = Keyboard::Down;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Right) && unitFrame_right.getPosition().x < 1380) {
				if (Keyboard::isKeyPressed(Keyboard::RShift) && unitGrid[spawnUnitRight_x][spawnUnitRight_y].getMovedOrNot() == false && unitGrid[spawnUnitRight_x][spawnUnitRight_y].getType() != unitType::EMPTY) {
					if (unitGrid[spawnUnitRight_x][spawnUnitRight_y].getLeftOrNot() == false) {
						if (unitGrid[spawnUnitRight_x + 1][spawnUnitRight_y].getLeftOrNot() == false || unitGrid[spawnUnitRight_x + 1][spawnUnitRight_y].getType() == unitType::EMPTY)unitGrid[spawnUnitRight_x][spawnUnitRight_y].move(unitGrid[spawnUnitRight_x + 1][spawnUnitRight_y]);
						else unitGrid[spawnUnitRight_x][spawnUnitRight_y].battle(unitGrid[spawnUnitRight_x + 1][spawnUnitRight_y]);
					}
				}
				unitFrame_right.setPosition(Vector2f(unitFrame_right.getPosition().x + 120, unitFrame_right.getPosition().y));
				spawnUnitRight_x++;
				inputStatusRed = e_inputStat::PAUSED;
				lastHitRed = Keyboard::Right;
			}
		}
		if (playerStatusBlue == e_playerStat::READY && playerStatusRed == e_playerStat::READY) {
			turnNumber++;
			turnDisplay.setString("Turn " + std::to_string(turnNumber));
			factoryOutput0 += factoryOutputDelta0;
			factoryOutput_Left.setString("Factory Output = " + std::to_string(factoryOutput0));
			factoryOutput1 += factoryOutputDelta1;
			factoryOutput_Right.setString("Factory Output = " + std::to_string(factoryOutput1));
			playerStatusBlue = e_playerStat::NOT_READY; playerStatusRed = e_playerStat::NOT_READY;
			for (int i = 0; i < 12; i++) {
				for (int j = 0; j < 5; j++) {
					unitGrid[i][j].setMovedOrNot(false);
				}
			}
		}

		window.clear();
		window.draw(spriteBackground);

		menuBar.setPosition(Vector2f(0, 0));
		window.draw(menuBar);
		for (int i = 0; i < 5; i++) {
			spriteMenu[i].setPosition(120 + i * 240, 75);
			spriteMenu[i].scale(-1, 1);
			window.draw(spriteMenu[i]);
		}
		window.draw(factoryOutput_Left);
		window.draw(turnDisplay);
		window.draw(frame_left);
		window.draw(unitFrame_left);

		menuBar.setPosition(Vector2f(0, 745));
		window.draw(menuBar);
		for (int i = 0; i < 5; i++) {
			spriteMenu[i].setPosition(1320 - i * 240, 825);
			spriteMenu[i].scale(-1, 1);
			window.draw(spriteMenu[i]);
		}
		window.draw(factoryOutput_Right);
		window.draw(frame_right);
		window.draw(unitFrame_right);

		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 5; j++) {
				if (unit::typeToNum(unitGrid[i][j].getType()) != -1) {
					spriteMenu[unit::typeToNum(unitGrid[i][j].getType())].scale(0.5, 0.5);
					spriteMenu[unit::typeToNum(unitGrid[i][j].getType())].setPosition(i * 120 + 60, j * 120 + 210);
					window.draw(spriteMenu[unit::typeToNum(unitGrid[i][j].getType())]);
					if (unitGrid[i][j].getLeftOrNot() == true) {
						tint.setFillColor(Color(0, 0, 255, 64));
						tint.setPosition(i * 120 + 60, j * 120 + 210);
						window.draw(tint);
					}
					else {
						tint.setFillColor(Color(255, 0, 0, 64));
						tint.setPosition(i * 120 + 60, j * 120 + 210);
						window.draw(tint);
					}
					std::stringstream ss;
					ss << std::fixed << std::setprecision(1) << unitGrid[i][j].getStrength();
					health.setString(ss.str());
					ss.clear();
					health.setPosition(Vector2f(i * 120 + 45, j * 120 + 220));
					window.draw(health);
					spriteMenu[unit::typeToNum(unitGrid[i][j].getType())].scale(2, 2);
				}
			}
		}
		window.display();
	}
}

vector <vector <Tile> >& initializer(Allegiance allegiances[2])
{
	ifstream saveFile;
	saveFile.open("save/default save.txt");
	
	string nameLeft, nameRight;
	saveFile >> nameLeft >> nameRight;
	allegiances[0].setName(nameLeft);
	allegiances[1].setName(nameRight);

	vector <vector <Tile> > tiles;

	int tileX, tileY;
	saveFile >> tileX >> tileY;

	int terrainNum, allegianceNum;
	for (int i = 0; i < tileX; i++) {
		for (int j = 0; j < tileY; j++) {
			saveFile >> terrainNum >> allegianceNum;
			allegiances[allegianceNum].addTile(i, j);
			Tile tempTile(terrainNum, allegiances[allegianceNum].getName());
			tiles[i].push_back(tempTile);
		}
	}

	return tiles;
}
