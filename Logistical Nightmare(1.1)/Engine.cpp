#include "pch.h"
#include "Engine.h"

float Engine::MAX_ZOOM;
float Engine::MIN_ZOOM;
float Engine::CAMERA_SENSITIVITY = 15.f;
float Engine::ZOOM_FACTOR_MAP = 1.f;
float Engine::ZOOM_FACTOR_PRODUCTION = 1.f;
std::vector<std::vector<Tile>> Engine::saveLoader(std::vector<Allegiance>& allegiances)
{
	std::ifstream saveFile;
	saveFile.open("saves/default save.txt");

	std::string nameLeft, nameRight;
	saveFile >> nameLeft >> nameRight;
	allegiances[0].setName(nameLeft);
	allegiances[1].setName(nameRight);

	allegianceText1.setString(nameLeft);
	allegianceText2.setString(nameRight);

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

//Easier than hard coding everything in the run method
void Engine::equipmentStatSetter()
{
	allResearch.emplace_back("graphics/kar98k.png", 0.f, 0.f, 15.f, 5.f, 90.f, sf::Vector2f(300, 100), 10, -1);
	allResearch.emplace_back("graphics/mp40.png", 0.f, 0.f, 30.f, 10.f, 79.f, sf::Vector2f(100, 300), 200, 0);
	allResearch.emplace_back("graphics/panzerschreck.png", 0.f, 60.f, 5.f, 20.f, 85.f, sf::Vector2f(100, 500), 450, 1);
	allResearch.emplace_back("graphics/panzerfaust.png", 0.f, 80.f, 2.f, 20.f, 80.f, sf::Vector2f(100, 700), 800, 2);
	allResearch.emplace_back("graphics/anti_tank.png", 0.f, 80.f, 2.f, 20.f, 80.f, sf::Vector2f(100, 900), 830, 3);
	allResearch.emplace_back("graphics/panzer_3_b.png", 30.f, 45.f, 25.f, 190.f, 92.f, sf::Vector2f(300, 300), 279, 0);
	allResearch.emplace_back("graphics/panzer_4_g.png", 60.f, 90.f, 27.f, 240.f, 89.f, sf::Vector2f(300, 500), 689, 5);
	allResearch.emplace_back("graphics/panther.png", 100.f, 145.f, 27.f, 320.f, 74.f, sf::Vector2f(300, 700), 756, 6);
	allResearch.emplace_back("graphics/tiger_2_p.png", 130.f, 180.f, 40.f, 550.f, 60.f, sf::Vector2f(500, 500), 1520, 6);
	allResearch.emplace_back("graphics/tiger_2_h.png", 160.f, 180.f, 40.f, 600.f, 65.f, sf::Vector2f(500, 700), 390, 8);
	allResearch.emplace_back("graphics/maus.png", 0.f, 80.f, 2.f, 20.f, 80.f, sf::Vector2f(500, 900), 2345, 9);
	allResearch.emplace_back("graphics/ConstructionPoints.png", 0.f, 80.f, 2.f, 20.f, 80.f, sf::Vector2f(700, 100), 10, -1);
}

//the general input method that runs every frame
void Engine::input(sf::RenderWindow& window, std::vector<sf::View>& views, sf::Vector2f resolution, e_tab& tabStatus, sf::Event& event, std::vector <std::vector <Tile> >& tiles)
{
	//To make the code more readable
	sf::View& mapView = views[static_cast<int>(e_views::MAP)];
	sf::View& hudView = views[static_cast<int>(e_views::HUD)];
	sf::View& resViewRight = views[static_cast<int>(e_views::RESEARCH_RIGHT)];
	sf::Vector2i screenPosition = sf::Mouse::getPosition(window);
	while (window.pollEvent(event)) {
		switch (event.type) 
		{   
		    case sf::Event::MouseWheelScrolled:
				if (tabStatus == e_tab::UNITS) {
					zoom(mapView, event.mouseWheelScroll.delta, Engine::ZOOM_FACTOR_MAP);
				}
				else if (tabStatus == e_tab::PRODUCTION || tabStatus == e_tab::PRODUCTION_CLICKED) {
					zoom(views[static_cast<int>(e_views::PRODUCTION)], event.mouseWheelScroll.delta, Engine::ZOOM_FACTOR_PRODUCTION);
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (screenPosition.y <= (resolution.y * 0.1f)) {
						hudInput(window.mapPixelToCoords(screenPosition, hudView), tabStatus);
					}
					else if (tabStatus == e_tab::UNITS) {

					}
					else if (tabStatus == e_tab::RESEARCH) {
						researchInput(window, views, screenPosition);
					}
					else if (tabStatus == e_tab::PRODUCTION || tabStatus == e_tab::PRODUCTION_CLICKED) {
						productionInput(window, views, screenPosition, tabStatus, tiles);
					}
					else if (tabStatus == e_tab::OPTIONS) {
						optionsInput(window.mapPixelToCoords(screenPosition, views[static_cast<int>(e_views::OPTIONS)]));
					}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					if (tabStatus == e_tab::UNITS) {
					}
				}
				break; }
			case sf::Event::MouseButtonReleased:
				if (tabStatus == e_tab::OPTIONS && event.mouseButton.button == sf::Mouse::Left) {
					if (zoomSensitivity.isClicked()) {
						zoomSensitivity.setClickedOrNot(false, window.mapPixelToCoords(screenPosition, views[static_cast<int>(e_views::OPTIONS)]));
					}
					if (cameraSensitivity.isClicked()) {
						cameraSensitivity.setClickedOrNot(false, window.mapPixelToCoords(screenPosition, views[static_cast<int>(e_views::OPTIONS)]));
					}
				}
				break;
			case sf::Event::TextEntered:
				if (tabStatus == e_tab::OPTIONS) {
					if (test.isClicked()) {
						test.addNumber(event.text.unicode);
					}
				}
				break;
		}
	}

	if (tabStatus == e_tab::UNITS) {
		cameraMover(mapView, sf::Vector2f(mapSize.x, mapSize.y), sf::Vector2f(0, 0));
	}
	else if (tabStatus == e_tab::PRODUCTION) {
		cameraMover(views[static_cast<int>(e_views::PRODUCTION)], sf::Vector2f(mapSize.x, mapSize.y), sf::Vector2f(0, 0));
	}
	else if (tabStatus == e_tab::PRODUCTION_CLICKED) {
		cameraMover(views[static_cast<int>(e_views::RESEARCH_LEFT)], sf::Vector2f(researchBackgroundLeft.getSize().x - resolution.x * 0.2f, researchBackgroundLeft.getSize().y - resolution.y * 0.45f), sf::Vector2f(resolution.x * 0.2f, resolution.y * 0.45f));
		researchFrameLeft.setPosition(views[static_cast<int>(e_views::RESEARCH_LEFT)].getCenter());
	}
	else if (tabStatus == e_tab::RESEARCH) {
		cameraMover(views[static_cast<int>(e_views::RESEARCH_LEFT)], sf::Vector2f(researchBackgroundLeft.getSize().x - resolution.x * 0.2f, researchBackgroundLeft.getSize().y - resolution.y * 0.45f), sf::Vector2f(resolution.x * 0.2f, resolution.y * 0.45f));
		researchFrameLeft.setPosition(views[static_cast<int>(e_views::RESEARCH_LEFT)].getCenter());
	}

	if (zoomSensitivity.isClicked()) {
		zoomSensitivity.setMovablePosition(window.mapPixelToCoords(screenPosition, views[static_cast<int>(e_views::OPTIONS)]));
		ZOOM_SENSITIVITY = zoomSensitivity.getVal();
	}
	if (cameraSensitivity.isClicked()) {
		cameraSensitivity.setMovablePosition(window.mapPixelToCoords(screenPosition, views[static_cast<int>(e_views::OPTIONS)]));
		CAMERA_SENSITIVITY = cameraSensitivity.getVal();
	}
}

void Engine::researchInput(sf::RenderWindow& window, std::vector<sf::View>& views, sf::Vector2i mouseLocalPosition)
{
	sf::Vector2f mouseGlobalPosition = window.mapPixelToCoords(mouseLocalPosition, views[static_cast<int>(e_views::RESEARCH_LEFT)]);
	sf::FloatRect bounds;
	for (auto& res : allResearch) {
		bounds = res.getEquipmentBackground().getGlobalBounds();
		if (bounds.contains(mouseGlobalPosition) && (res.prevResearchVectorLocation == -1 || allResearch[res.prevResearchVectorLocation].isResearched() == e_researchStatus::RESEARCHED)) {
			res.doResearch();
		}
	}
}

void Engine::productionInput(sf::RenderWindow & window, std::vector<sf::View>& views, sf::Vector2i mouseLocalPosition, e_tab& tabStatus, std::vector <std::vector <Tile> >& tiles)
{
	if (tabStatus == e_tab::PRODUCTION) {
		sf::Vector2f mouseProductionPosition = window.mapPixelToCoords(mouseLocalPosition, views[static_cast<int>(e_views::PRODUCTION)]);
		if (mouseProductionPosition.x >= 0 && mouseProductionPosition.x < mapSize.x && mouseProductionPosition.y >= 0 && mouseProductionPosition.y < mapSize.y) {
			productionSelectedTile = sf::Vector2i(static_cast<int>(mouseProductionPosition.x / TILE_SIZE), static_cast<int>(mouseProductionPosition.y / TILE_SIZE));
			if (tiles[productionSelectedTile.x][productionSelectedTile.y].hasFactory()) {
				tabStatus = e_tab::PRODUCTION_CLICKED;
				views[static_cast<int>(e_views::PRODUCTION)].setCenter(TILE_SIZE * (productionSelectedTile.x + 0.5f), TILE_SIZE * (productionSelectedTile.y + 0.5f));
			}
			else if (allegiances[0].getConstructionPoints() > 2500.f) {
				tiles[productionSelectedTile.x][productionSelectedTile.y].addFactory();
				allegiances[0].setConstructionPoints(allegiances[0].getConstructionPoints() - 2500.f);
			}
		}
	}
	else if (tabStatus == e_tab::PRODUCTION_CLICKED) {
		//std::cout << mouseLocalPosition.x << " " << mouseLocalPosition.y << std::endl;
		if (mouseLocalPosition.x < (resolution.x * 0.4f)) {
			sf::Vector2f mouseResPosition = window.mapPixelToCoords(mouseLocalPosition, views[static_cast<int>(e_views::RESEARCH_LEFT)]);
			sf::FloatRect bounds;
			for (auto& res : allResearch) {
				bounds = res.getEquipmentBackground().getGlobalBounds();
				if (bounds.contains(mouseResPosition) && res.isResearched() == e_researchStatus::RESEARCHED) {
					tiles[productionSelectedTile.x][productionSelectedTile.y].setEquipmentInProduction(res.getEquipment().getName(),  res.getEquipment().getProductionCost());
					tabStatus = e_tab::PRODUCTION;
					break;
				}
			}
		}
		else {
			sf::Vector2f mouseProductionPosition = window.mapPixelToCoords(mouseLocalPosition, views[static_cast<int>(e_views::PRODUCTION)]);
			if (mouseProductionPosition.x >= 0 && mouseProductionPosition.x < mapSize.x && mouseProductionPosition.y >= 0 && mouseProductionPosition.y < mapSize.y) {
				productionSelectedTile = sf::Vector2i(static_cast<int>(mouseProductionPosition.x / TILE_SIZE), static_cast<int>(mouseProductionPosition.y / TILE_SIZE));
				if (tiles[productionSelectedTile.x][productionSelectedTile.y].hasFactory()) {
					tabStatus = e_tab::PRODUCTION_CLICKED;
					views[static_cast<int>(e_views::PRODUCTION)].setCenter(TILE_SIZE * (productionSelectedTile.x + 0.5f), TILE_SIZE * (productionSelectedTile.y + 0.5f));
				}
			}
		}
	}
}

void Engine::optionsInput(sf::Vector2f mouseGlobalPos)
{
	if (zoomSensitivity.movableContains(mouseGlobalPos) && zoomSensitivity.isClicked() == false) {
		zoomSensitivity.setClickedOrNot(true, mouseGlobalPos);
	}
	if (cameraSensitivity.movableContains(mouseGlobalPos) && zoomSensitivity.isClicked() == false) {
		cameraSensitivity.setClickedOrNot(true, mouseGlobalPos);
	}
	if (!test.setClickedTrue(mouseGlobalPos)) {
		test.setClickedFalse();
	}
}

void Engine::zoom(sf::View& mapView, float scrollDelta, float& zoomFactor)
{
	if (zoomFactor < MAX_ZOOM && scrollDelta > 0) {
		zoomFactor += ZOOM_SENSITIVITY;
		if (zoomFactor > MAX_ZOOM)zoomFactor = MAX_ZOOM;
		mapView.setSize(resolution.x * zoomFactor, resolution.y * 0.9 * zoomFactor);
	}
	else if (zoomFactor > MIN_ZOOM && scrollDelta < 0) {
		zoomFactor -= ZOOM_SENSITIVITY;
		if (zoomFactor < MIN_ZOOM)zoomFactor = MIN_ZOOM;
		mapView.setSize(resolution.x * zoomFactor, resolution.y * 0.9 * zoomFactor);
	}
}

void Engine::cameraMover(sf::View& view, sf::Vector2f boundsMax, sf::Vector2f boundsMin)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && view.getCenter().y > (CAMERA_SENSITIVITY + boundsMin.y)) {
		view.setCenter(sf::Vector2f(view.getCenter().x, view.getCenter().y - CAMERA_SENSITIVITY));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && view.getCenter().y < (boundsMax.y - CAMERA_SENSITIVITY)) {
		view.setCenter(sf::Vector2f(view.getCenter().x, view.getCenter().y + CAMERA_SENSITIVITY));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && view.getCenter().x > (CAMERA_SENSITIVITY + boundsMin.x)) {
		view.setCenter(sf::Vector2f(view.getCenter().x - CAMERA_SENSITIVITY, view.getCenter().y));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && view.getCenter().x < (boundsMax.x - CAMERA_SENSITIVITY)) {
		view.setCenter(sf::Vector2f(view.getCenter().x + CAMERA_SENSITIVITY, view.getCenter().y));
	}
}

void Engine::hudInput(sf::Vector2f mouseHudPos, e_tab& tab)
{
	if (mouseHudPos.y > (resolution.y * 0.05f)) {
		switch (int (mouseHudPos.x / (resolution.x / 6))) {
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
	if (speedButtons.getGlobalBounds().contains(mouseHudPos)) {
		switch (static_cast<int>((mouseHudPos.x - speedButtons.getGlobalBounds().left) / (speedButtons.getGlobalBounds().width / 5))) {
		    case 0:
				GAME_SPEED = 0;
				gameSpeedButtonShade.setPosition(resolution.x * 0.4f, speedButtons.getGlobalBounds().top);
				break;
			case 1:
				GAME_SPEED = 1;
				gameSpeedButtonShade.setPosition(resolution.x * 0.4f + speedButtons.getLocalBounds().width * 0.2f * 0.4f, speedButtons.getGlobalBounds().top);
				break;
			case 2:
				GAME_SPEED = 4;
				gameSpeedButtonShade.setPosition(resolution.x * 0.4f + speedButtons.getLocalBounds().width * 0.4f * 0.4f, speedButtons.getGlobalBounds().top);
				break;
			case 3:
				GAME_SPEED = 8;
				gameSpeedButtonShade.setPosition(resolution.x * 0.4f + speedButtons.getLocalBounds().width * 0.6f * 0.4f, speedButtons.getGlobalBounds().top);
				break;
			case 4:
				GAME_SPEED = 16;
				gameSpeedButtonShade.setPosition(resolution.x * 0.4f + speedButtons.getLocalBounds().width * 0.8f * 0.4f, speedButtons.getGlobalBounds().top);
				break;
		}
	}
}

void Engine::run()
{
	//start
	allegiances.push_back(Allegiance());
	allegiances.push_back(Allegiance());
    std::vector <std::vector <Tile> > tiles = saveLoader(allegiances);

	tilesNums = sf::Vector2i(tiles.size(), tiles[0].size());
	mapSize = sf::Vector2f(tilesNums.x * TILE_SIZE, tilesNums.y * TILE_SIZE);
	e_gameStat gameStatus = e_gameStat::RUNNING;
	//Max zoom and min zoom and setting the blue map background ( Did this way to prevent size distortion because of the different ratios between the map size and screen size)
	if (mapSize.x / resolution.x < mapSize.y / resolution.y) {
		MAX_ZOOM = mapSize.y / resolution.y / 0.9f;
		MIN_ZOOM = mapSize.y / resolution.y / 0.9f / 4.f;
	}
	else {
		MAX_ZOOM = mapSize.x / resolution.x;
		MIN_ZOOM = mapSize.x / resolution.x / 4.f;
	}
	//Setting map background up
	mapBackground.setPosition(sf::Vector2f(-resolution.x / 2 * MAX_ZOOM, -resolution.y * 0.9f / 2 * MAX_ZOOM));
	mapBackground.setSize(sf::Vector2f((resolution.x + mapSize.x) * MAX_ZOOM, (resolution.y * 0.9 + mapSize.y) * MAX_ZOOM));
	//Creating the window
	sf::VideoMode vm(resolution.x, resolution.y);
	sf::RenderWindow window(vm, "Logistical Nightmare", sf::Style::Fullscreen);
	window.setFramerateLimit(90);

	//Views (don't mess with the push_back order)
	std::vector<sf::View> views;
	views.push_back(sf::View(sf::FloatRect(0, 0, resolution.x, resolution.y * 0.1f)));
	views[0].setViewport(sf::FloatRect(0, 0, 1, 0.1f));
	views.push_back(sf::View(sf::Vector2f(mapSize.x / 2, mapSize.y / 2), sf::Vector2f(resolution.x, resolution.y * 0.9f)));
	views[1].setViewport(sf::FloatRect(0, 0.1f, 1, 0.9f));
	views.push_back(sf::View(sf::FloatRect(0, 0, resolution.x * 0.4f, resolution.y * 0.9f)));
	views[2].setViewport(sf::FloatRect(0.f, 0.1f, 0.4f, 0.9f));
	views.push_back(sf::View(sf::FloatRect(0, 0, resolution.x * 0.1f, resolution.y * 0.9f)));
	views[3].setViewport(sf::FloatRect(0.9f, 0.1f, 0.1f, 0.9f));
	views.push_back(sf::View(sf::Vector2f(mapSize.x / 2, mapSize.y / 2), sf::Vector2f(resolution.x, resolution.y * 0.9f)));
	views[4].setViewport(sf::FloatRect(0, 0.1f, 1, 0.9f));
	views.push_back(sf::View(sf::Vector2f(mapSize.x / 2, mapSize.y / 2), sf::Vector2f(resolution.x, resolution.y * 0.9f)));
	views[5].setViewport(sf::FloatRect(0, 0.1f, 1, 0.9f));
	views.push_back(sf::View(sf::Vector2f(mapSize.x / 2, mapSize.y / 2), sf::Vector2f(resolution.x, resolution.y * 0.9f)));
	views[6].setViewport(sf::FloatRect(0, 0.1f, 1, 0.9f));
	views.push_back(sf::View(sf::Vector2f(resolution.x / 4, resolution.y * 0.225f), sf::Vector2f(resolution.x / 2, resolution.y * 0.45f)));
	views[7].setViewport(sf::FloatRect(0.25f, 0.325f, 0.5f, 0.45f));
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
			deltaTime = clock.restart().asSeconds() * Renderer::GAME_SPEED;
			runTime += deltaTime;
			//updating the tiles and thr two sides (allegiances)
			for (int i = 0; i < 2; i++) {
				allegiances[i].update(deltaTime, tiles);
			}
			//updating the research
			for (auto& res : allResearch) {
				if (res.isResearched() == e_researchStatus::IN_PROGRESS) {
					res.update(Renderer::GAME_SPEED);
				}
			}
			allegianceText1.setString(allegiances[0].getName() + " CP: " + std::to_string(static_cast<int>(allegiances[0].getConstructionPoints())));
			allegianceText2.setString(allegiances[1].getName() + " CP: " + std::to_string(static_cast<int>(allegiances[1].getConstructionPoints())));
			input(window, views, resolution, tabStatus, event, tiles);
			drawToWindow(window, views, tabStatus, tiles);
			window.display();
			window.clear();
		}
	}
}
