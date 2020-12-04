#include "pch.h"
#include "Engine.h"

std::vector<std::vector<Tile>> Engine::saveLoader(std::vector<Allegiance>& allegiances)
{
	std::ifstream saveFile;
	saveFile.open("saves/default save.txt");

	std::string nameLeft, nameRight;
	saveFile >> nameLeft >> nameRight;
	allegiances[0].setName(nameLeft);
	allegiances[1].setName(nameRight);

	m_allegiance1.setString(nameLeft);
	m_allegiance2.setString(nameRight);

	std::vector <std::vector <Tile> > tiles;

	int tileX, tileY;
	saveFile >> tileX >> tileY;

	std::vector<Tile> tempvec;
	for (int i = 0; i < tileX; i++) {
		tiles.push_back(tempvec);
	}

	int terrainNum, allegianceNum;
	for (int i = 0; i < tileX; i++) {
		for (int j = 0; j < tileY; j++) {
			saveFile >> terrainNum >> allegianceNum;
			Tile tempTile(terrainNum, sf::Vector2i(i, j));
			tiles[i].push_back(tempTile);
			allegiances[allegianceNum].addTile(sf::Vector2i(i, j));
		}
	}
	int factoryCooX, factoryCooY;
	while (saveFile.peek() != EOF) {
		saveFile >> factoryCooX >> factoryCooY;
		tiles[factoryCooX][factoryCooY].addFactory();
	}
	saveFile.close();
	return tiles;
}

void Engine::equipmentStatSetter()
{
	infantryRes.push_back(Researchable("graphics/kar98k.png", 0.f, 0.f, 15.f, 5.f, 90.f, sf::Vector2f(0, 0), 10));
	infantryRes.push_back(Researchable("graphics/mp40.png", 0.f, 0.f, 30.f, 10.f, 79.f, sf::Vector2f(0, 100), 100));
	infantryRes.push_back(Researchable("graphics/panzerschreck.png", 0.f, 60.f, 5.f, 20.f, 85.f, sf::Vector2f(0, 200), 200));
	infantryRes.push_back(Researchable("graphics/panzerfaust.png", 0.f, 80.f, 2.f, 20.f, 80.f, sf::Vector2f(0, 300), 400));
	tankRes.push_back(Researchable("graphics/panzer_3_b.png", 30.f, 45.f, 25.f, 190.f, 92.f, sf::Vector2f(200, 0), 150));
	tankRes.push_back(Researchable("graphics/panzer_4_g.png", 60.f, 90.f, 27.f, 240.f, 89.f, sf::Vector2f(200, 100), 150));
	tankRes.push_back(Researchable("graphics/panther.png", 100.f, 145.f, 27.f, 320.f, 74.f, sf::Vector2f(200, 200), 400));
	tankRes.push_back(Researchable("graphics/tiger_2_p.png", 130.f, 180.f, 40.f, 550.f, 60.f, sf::Vector2f(200, 300), 800));
	tankRes.push_back(Researchable("graphics/tiger_2_h.png", 160.f, 180.f, 40.f, 600.f, 65.f, sf::Vector2f(200, 400), 800));
	antiTankRes.push_back(Researchable("graphics/anti_tank.png", 0.f, 80.f, 2.f, 20.f, 80.f, sf::Vector2f(400, 0), 400));
}

void Engine::input(sf::RenderWindow& window, sf::View& hudView, sf::View& uiView, sf::View& mapView, sf::Vector2f resolution, e_tab& tabStatus, sf::Event& event)
{
	while (window.pollEvent(event)) {
		switch (event.type) 
		{   
		    case sf::Event::MouseWheelScrolled:
				if (tabStatus == e_tab::UNITS) {
					zoom(mapView, event.mouseWheelScroll.delta);
				}
				break;
			case sf::Event::MouseButtonPressed:
				sf::Vector2i screenPosition = sf::Mouse::getPosition(window);
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (screenPosition.y <= (resolution.y * 0.15)) {
						hudInput(window.mapPixelToCoords(screenPosition, hudView), tabStatus);
					}
					else if (tabStatus == e_tab::UNITS) {
						//noneInput(window.mapPixelToCoords(screenPosition, mapView), tabStatus, true);
					}
					else if (tabStatus == e_tab::RESEARCH) {
						researchInput(window.mapPixelToCoords(screenPosition, uiView));
					}
					else if (tabStatus == e_tab::PRODUCTION) {
						//FIXME
						//tileInput();
					}
				}
				else if (event.mouseButton.button == sf::Mouse::Right){
					if (tabStatus == e_tab::UNITS) {
						//noneInput(window.mapPixelToCoords(screenPosition, mapView), tabStatus, false);
					}
				}
				break;
		}
	}
}

void Engine::researchInput(sf::Vector2f mouseGlobalPosition)
{
	sf::FloatRect bounds;
	for (auto& res : infantryRes) {
		bounds = res.getEquipmentBackground().getGlobalBounds();
		if (bounds.contains(mouseGlobalPosition)) {
			res.doResearch();
		}
	}
	for (auto& res : tankRes) {
		bounds = res.getEquipmentBackground().getGlobalBounds();
		if (bounds.contains(mouseGlobalPosition)) {
			res.doResearch();
		}
	}
	for (auto& res : antiTankRes) {
		bounds = res.getEquipmentBackground().getGlobalBounds();
		if (bounds.contains(mouseGlobalPosition)) {
			res.doResearch();
		}
	}
}

void Engine::zoom(sf::View& mapView, float scrollDelta)
{
	mapView.zoom(1 + m_ZOOM_SENSITIVITY * scrollDelta);
}

void Engine::hudInput(sf::Vector2f mouseHudPos, e_tab& tab)
{
	if (mouseHudPos.y > (m_resolution.y * 0.075f)) {
		switch (int (mouseHudPos.x / (m_resolution.x / 6))) {
		    case 0:
				tab = e_tab::UNITS;
				break;
			case 1:
				tab = e_tab::RESEARCH;
				break;
			case 2:
				tab = e_tab::PRODUCTION;
				break;
			case 3:
				tab = e_tab::LOGISTICS;
				break;
			case 4:
				tab = e_tab::BUILDING;
				break;
			case 5:
				tab = e_tab::OPTIONS;
				break;
			default:
				tab = e_tab::OPTIONS;
				break;
		}
	}
}

void Engine::run()
{
	//start
	std::vector <Allegiance> allegiances;
	allegiances.push_back(Allegiance());
	allegiances.push_back(Allegiance());
    std::vector <std::vector <Tile> > tiles = saveLoader(allegiances);

	m_tilesNums = sf::Vector2f(tiles.size(), tiles[0].size());
	m_mapSize = sf::Vector2f(m_tilesNums.x * m_TILE_SIZE, m_tilesNums.y * m_TILE_SIZE);
	e_gameStat gameStatus = e_gameStat::RUNNING;

	//Creating the window
	sf::VideoMode vm(m_resolution.x, m_resolution.y);
	sf::RenderWindow window(vm, "Logistical Nightmare", sf::Style::Fullscreen);
	window.setFramerateLimit(30);

	//Views
	sf::View hudView(sf::FloatRect(0, 0, m_resolution.x, m_resolution.y * 0.15f));
	hudView.setViewport(sf::FloatRect(0, 0, 1, 0.15f));
	sf::View uiView(sf::FloatRect(0, 0, m_resolution.x, m_resolution.y * 0.85f));
	uiView.setViewport(sf::FloatRect(0, 0.15f, 1, 0.85f));
	sf::View mapView;
	mapView.setViewport(sf::FloatRect(0, 0.15f, 1, 0.85f));
	mapView.setSize(m_resolution.x, m_resolution.y * 0.85f);
	mapView.setCenter(m_mapSize.x / 2, m_mapSize.y / 2);

	//Tab status
	e_tab tabStatus = e_tab::UNITS;

	//Event for input
	sf::Event event;

	//Runtime clock
	sf::Clock clock; float deltaTime;

	//Setting stats for equipments
	equipmentStatSetter();

	while (window.isOpen()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
		}
		else {
			deltaTime = clock.restart().asSeconds();
			runTime += deltaTime;
			//updating the tiles and thr two sides (allegiances)
			for (int i = 0; i < 2; i++) {
				allegiances[i].update(deltaTime, tiles);
			}
			m_allegianceCP1.setString("CP: " + std::to_string(int(allegiances[0].getConstructionPoints())));
			m_allegianceCP2.setString("CP: " + std::to_string(int(allegiances[1].getConstructionPoints())));
			//updating the research
			for (auto& res : infantryRes) {
				res.update();
			}
			for (auto& res : tankRes) {
				res.update();
			}
			for (auto& res : antiTankRes) {
				res.update();
			}

			input(window, hudView, uiView, mapView, m_resolution, tabStatus, event);
			drawToWindow(window, hudView, uiView, mapView, tabStatus, tiles);
			window.display();
			window.clear();
		}
	}
}
