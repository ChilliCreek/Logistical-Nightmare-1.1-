#include "pch.h"
#include "Engine.h"

vector<vector<Tile>>& Engine::saveLoader(Allegiance allegiances[2])
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
			Tile tempTile(terrainNum);
			tiles[i].push_back(tempTile);
			allegiances[allegianceNum].addTile(i, j, &tiles[i][j]);
		}
	}
	saveFile.close();
	return tiles;
}

void Engine::input(RenderWindow& window, View& hudView, View& uiView, View& mapView, Vector2f resolution, e_tab& tabStatus)
{
	Vector2i screenPosition = Mouse::getPosition(window);
	if (screenPosition.y < (resolution.y * 0.15)) {
		hudInput(window.mapPixelToCoords(screenPosition, hudView), tabStatus);
	}
	else if (tabStatus == e_tab::NONE) {

	}
}

void Engine::run()
{
	Allegiance* allegiances = new Allegiance[2];
	vector <vector <Tile> >& tiles = saveLoader(allegiances);

	e_gameStat gameStatus = e_gameStat::RUNNING;
	//resolution 
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	//Creating the window
	VideoMode vm(resolution.x, resolution.y);
	RenderWindow window(vm, "Logistical Nightmare", Style::Fullscreen);
	//Views
	View hudView(sf::FloatRect(0, 0, resolution.x * 0.15, resolution.y * 0.15));
	View uiView(sf::FloatRect(0, resolution.y * 0.15, resolution.x, resolution.y * 0.85));
	View mapView(sf::FloatRect(0, resolution.y * 0.15, resolution.x, resolution.y * 0.85));
	//Font
	Font font;
	font.loadFromFile("font/Stanberry.ttf");
	//Tab status
	e_tab tabStatus = e_tab::NONE;

	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		else {
			input(window, hudView, uiView, mapView, resolution, tabStatus);
		}
	}

	delete[] allegiances;
	allegiances = nullptr;
}
