#include "pch.h"
#include "Engine.h"

vector<vector<Tile>> Engine::saveLoader(vector<Allegiance>& allegiances)
{
	ifstream saveFile;
	saveFile.open("saves/default save.txt");

	string nameLeft, nameRight;
	saveFile >> nameLeft >> nameRight;
	allegiances[0].setName(nameLeft);
	allegiances[1].setName(nameRight);

	allegiance1.setString(nameLeft);
	allegiance2.setString(nameRight);

	vector <vector <Tile> > tiles;

	int tileX, tileY;
	saveFile >> tileX >> tileY;

	vector<Tile> tempvec;
	for (int i = 0; i < tileX; i++) {
		tiles.push_back(tempvec);
	}

	int terrainNum, allegianceNum;
	for (int i = 0; i < tileX; i++) {
		for (int j = 0; j < tileY; j++) {
			saveFile >> terrainNum >> allegianceNum;
			Tile tempTile(terrainNum);
			tiles[i].push_back(tempTile);
			allegiances[allegianceNum].addTile(Vector2i(i, j));
		}
	}
	saveFile.close();
	return tiles;
}

void Engine::equipmentStatSetter()
{
	infantryRes.push_back(Researchable("graphics/kar98k.png", 0.f, 0.f, 10.f, 5.f, 90.f, Vector2f(0, 0), 10));
	infantryRes.push_back(Researchable("graphics/anti_tank.png", 5.f, 90.f, 2.f, 40.f, 80.f, Vector2f(0, 100), 100));
	tankRes.push_back(Researchable("graphics/panzer_3_b.png", 30.f, 45.f, 10.f, 190.f, 78.f, Vector2f(200, 0), 150));
	tankRes.push_back(Researchable("graphics/tiger_2_p.png", 120.f, 200.f, 20.f, 550.f, 60.f, Vector2f(200, 100), 300));
}

void Engine::input(RenderWindow& window, View& hudView, View& uiView, View& mapView, Vector2f resolution, e_tab& tabStatus, Event& event)
{
	while (window.pollEvent(event)) {
		switch (event.type) 
		{   
		    case Event::MouseWheelScrolled:
				if (tabStatus == e_tab::NONE) {
					zoom(mapView, event.mouseWheelScroll.delta);
				}
				break;
			case Event::MouseButtonPressed:
				Vector2i screenPosition = Mouse::getPosition(window);
				if (event.mouseButton.button == Mouse::Left) {
					if (screenPosition.y < (resolution.y * 0.15)) {
						hudInput(window.mapPixelToCoords(screenPosition, hudView), tabStatus);
					}
					else if (tabStatus == e_tab::NONE) {
						//noneInput(window.mapPixelToCoords(screenPosition, mapView), tabStatus, true);
					}
					else if (tabStatus == e_tab::RESEARCH) {
						//FIXME
						//researchInput();
					}
					else if (tabStatus == e_tab::TILE) {
						//FIXME
						//tileInput();
					}
				}
				else if (event.mouseButton.button == Mouse::Right){
					if (tabStatus == e_tab::NONE) {
						//noneInput(window.mapPixelToCoords(screenPosition, mapView), tabStatus, false);
					}
				}
				break;
		}
	}
}

void Engine::zoom(View& mapView, float scrollDelta)
{
	if (scrollDelta > 0) {
		if ((mapView.getSize().x + 10 * scrollDelta) > mapSize.x) {
			mapView.setSize(mapSize);
		}
		else {
			mapView.setSize(Vector2f(mapView.getSize().x + 10 * scrollDelta, mapView.getSize().y + 10.f / mapSize.x * mapSize.y * scrollDelta));
		}
	}
	else {
		if ((mapView.getSize().x - 10 * scrollDelta) < (mapSize.x / 3)) {
			mapView.setSize(Vector2f(mapSize.x / 3, mapSize.y / 3));
		}
		else {
			mapView.setSize(Vector2f(mapView.getSize().x - 10 * scrollDelta, mapView.getSize().y - 10.f / mapSize.x * mapSize.y * scrollDelta));
		}
	}
}

void Engine::hudInput(Vector2f mouseHudPos, e_tab& tab)
{
	if (mouseHudPos.y > (resolution.y * 0.075f)) {
		switch (int (mouseHudPos.x / (resolution.x / 6))) {
		    case 0:
				tab = e_tab::NONE;
				break;
			case 1:
				tab = e_tab::RESEARCH;
				break;
			case 2:
				tab = e_tab::FACTORY;
				break;
			default:
				tab = e_tab::NONE;
		}
	}
}

void Engine::drawToWindow(RenderWindow& window, View& hudView, View& uiView, View& mapView, e_tab& tabs)
{
	drawHudToWindow(window, hudView);
	//drawMapToWindow(window, mapView);
	switch (tabs) {
	    case e_tab::RESEARCH:
		    drawResearchToWindow(window, uiView);
			break;
		case e_tab::TILE:
			//drawTileToWindow(window, uiView);
			break;
		case e_tab::FACTORY:
			//drawFactoryToWindow(window, uiView);
			break;
		case e_tab::STORAGE:
			//drawFactoryToWindow(window, uiView);
		default:
			break;
	}
}

void Engine::drawHudToWindow(RenderWindow& window, View& hudView)
{
	window.setView(hudView);
	window.draw(hudBackground);
	window.draw(allegiance1);
	window.draw(allegiance2);
	for (int i = 0; i < 2; i++) {
		window.draw(tabs[i]);
	}
}

void Engine::drawResearchToWindow(RenderWindow& window, View& uiView)
{
	window.setView(uiView);
	window.draw(researchBackground);
	for (auto& res : infantryRes) {
		window.draw(res.getEquipment().getEquipmentSprite());
	}
	for (auto& res : tankRes) {
		window.draw(res.getEquipment().getEquipmentSprite());
	}
}

void Engine::run()
{
	//start
	vector <Allegiance> allegiances;
	allegiances.push_back(Allegiance());
	allegiances.push_back(Allegiance());

	vector <vector <Tile> > tiles = saveLoader(allegiances);
	tilesNums = Vector2f(tiles.size(), tiles[0].size());
	mapSize = Vector2f(tilesNums.x * 100, tilesNums.y * 100);

	e_gameStat gameStatus = e_gameStat::RUNNING;
	//Creating the window
	VideoMode vm(resolution.x, resolution.y);
	RenderWindow window(vm, "Logistical Nightmare", Style::Fullscreen);
	//Views
	View hudView(FloatRect(0, 0, resolution.x, resolution.y * 0.15f));
	hudView.setViewport(FloatRect(0, 0, 1, 0.15f));
	View uiView(FloatRect(0, 0, resolution.x, resolution.y * 0.85f));
	uiView.setViewport(FloatRect(0, 0.15f, 1, 1));
	View mapView(FloatRect(0, 0, mapSize.x, mapSize.y));
	mapView.setViewport(FloatRect(0, 0.15f, 1, 1));
	mapView.setCenter(Vector2f(mapSize.x / 2, mapSize.y / 2));
	//Tab status
	e_tab tabStatus = e_tab::NONE;
	//Event for input
	Event event;
	//Runtime clock
	Clock runTime; float elapsedTime;
	//Launching TextureHolder
	TextureHolder textureHolder;
	//Setting stats for equipments
	equipmentStatSetter();

	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		else {
			elapsedTime = runTime.restart().asSeconds();
			for (int i = 0; i < 2; i++) {
				allegiances[i].update(elapsedTime, tiles);
			}
			input(window, hudView, uiView, mapView, resolution, tabStatus, event);
			drawToWindow(window, hudView, uiView, mapView, tabStatus);
			window.display();
			window.clear();
		}
	}
}
Engine::Engine() 
{
	//resolution 
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	//hud background
	Color brown(150, 75, 0, 255);
	hudBackground.setFillColor(brown);
	hudBackground.setPosition(0, 0);
	hudBackground.setSize(Vector2f(resolution.x, resolution.y * 0.15f));
	//research background
	researchBackground.setFillColor(brown);
	researchBackground.setPosition(0, 0);
	researchBackground.setSize(Vector2f(400, 600));
	//map background
	mapBackground.setFillColor(Color::Green);
	mapBackground.setPosition(0, 0);
	mapBackground.setSize(mapSize);
	//font set
	font.loadFromFile("font/Stanberry.ttf");
	//Allegiance names
	allegiance1.setFont(font);
	allegiance2.setFont(font);
	allegiance1.setCharacterSize(10);
	allegiance2.setCharacterSize(10);
	allegiance1.setPosition(0, 0);
	allegiance2.setPosition(resolution.x * 0.80f, 0);
	//Tabs
	for (int i = 0; i < 6; i++) {
		tabs[i].setCharacterSize(20);
		tabs[i].setPosition((resolution.x / 6) * i, resolution.y * 0.1);
		tabs[i].setFont(font);
	}
	tabs[0].setString("Map");
	tabs[1].setString("Research");
}
