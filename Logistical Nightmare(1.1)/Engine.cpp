#include "pch.h"
#include "Engine.h"

float Engine::MAX_ZOOM;
float Engine::MIN_ZOOM;
float Engine::CAMERA_SENSITIVITY = 15.f;
float Engine::ZOOM_FACTOR_MAP = 1.f;
float Engine::ZOOM_FACTOR_PRODUCTION = 1.f;
Tile*** Engine::saveLoader(std::vector<Allegiance>& allegiances)
{
	std::ifstream saveFile;
	saveFile.open("saves/default save.txt");

	std::string nameLeft, nameRight;
	saveFile >> nameLeft >> nameRight;
	allegiances[0].setName(nameLeft);
	allegiances[1].setName(nameRight);

	allegianceText1.setString(nameLeft);
	allegianceText2.setString(nameRight);
	
	saveFile >> tilesNums.x >> tilesNums.y;

	Tile*** tiles = new Tile**[tilesNums.x];
	for (int i = 0; i < tilesNums.x; i++) {
		tiles[i] = (Tile**)malloc(sizeof(Tile*) * tilesNums.y);
		int terrainNum, allegianceNum;
		for (int j = 0; j < tilesNums.y; j++) {
			saveFile >> terrainNum >> allegianceNum;
			tiles[i][j] = new Tile(terrainNum, sf::Vector2i(i, j), allegianceNum);
			allegiances[allegianceNum].addTile(sf::Vector2i(i, j));
		}
	}
	int factoryCooX, factoryCooY;
	while (saveFile >> factoryCooX >> factoryCooY) {
		tiles[factoryCooX][factoryCooY]->addFactory();
	} 
	saveFile.close();
	return tiles;
}

//Easier than hard coding everything in the run method
void Engine::equipmentStatSetter()
{
	allResearch.emplace_back("graphics/kar98k.png", 0.f, 0.f, 15.f, 20.f, 90.f, sf::Vector2f(300, 100), 10, -1);
	allResearch.emplace_back("graphics/mp40.png", 0.f, 0.f, 30.f, 40.f, 79.f, sf::Vector2f(100, 300), 200, 0);
	allResearch.emplace_back("graphics/panzerschreck.png", 0.f, 60.f, 5.f, 200.f, 85.f, sf::Vector2f(100, 500), 450, 1);
	allResearch.emplace_back("graphics/panzerfaust.png", 0.f, 80.f, 2.f, 200.f, 80.f, sf::Vector2f(100, 700), 800, 2);
	allResearch.emplace_back("graphics/anti_tank.png", 0.f, 80.f, 2.f, 200.f, 80.f, sf::Vector2f(100, 900), 830, 3);
	allResearch.emplace_back("graphics/panzer_3_b.png", 30.f, 45.f, 25.f, 4000.f, 92.f, sf::Vector2f(300, 300), 279, 0);
	allResearch.emplace_back("graphics/panzer_4_g.png", 60.f, 90.f, 27.f, 4800.f, 89.f, sf::Vector2f(300, 500), 689, 5);
	allResearch.emplace_back("graphics/panther.png", 100.f, 145.f, 27.f, 6400.f, 74.f, sf::Vector2f(300, 700), 756, 6);
	allResearch.emplace_back("graphics/tiger_2_p.png", 130.f, 180.f, 40.f, 11000.f, 60.f, sf::Vector2f(500, 500), 1520, 6);
	allResearch.emplace_back("graphics/tiger_2_h.png", 160.f, 180.f, 40.f, 12000.f, 65.f, sf::Vector2f(500, 700), 390, 8);
	allResearch.emplace_back("graphics/maus.png", 200.f, 200.f, 40.f, 25000.f, 65.f, sf::Vector2f(500, 900), 2345, 9);
	allResearch.emplace_back("graphics/ConstructionPoints.png", 0.f, 80.f, 2.f, 200.f, 80.f, sf::Vector2f(700, 100), 10, -1);
}

int Engine::handleTime(int&hours, float sec)
{
	static float deltaTime = 0;
	deltaTime += sec;
	int newHours = static_cast<int>(deltaTime / (TIME_RATIO / GAME_SPEED));
	deltaTime = fmod(deltaTime, TIME_RATIO / GAME_SPEED);
	hours = hours + newHours;
	return newHours;
}

//the general input method that runs every frame
void Engine::input(sf::RenderWindow& window, std::vector<std::shared_ptr<sf::View>>& views, sf::Vector2f resolution, e_tab& tabStatus, Tile*** tiles)
{
	//To make the code more readable
	sf::View& mapView = *views[e_views::MAP];
	sf::View& hudView = *views[e_views::HUD];
	sf::View& resViewRight = *views[e_views::RESEARCH_RIGHT];
	sf::Vector2i screenPosition = sf::Mouse::getPosition(window);
	while (window.pollEvent(event)) {
		switch (event.type) 
		{   
		    case sf::Event::MouseWheelScrolled:
				if (tabStatus == e_tab::UNITS || (tabStatus == e_tab::LOGISTICS && selectedLogisticsTile.x == -1)) {
					zoom(views[e_views::MAP], event.mouseWheelScroll.delta, Engine::ZOOM_FACTOR_MAP);
				}
				else if (tabStatus == e_tab::PRODUCTION || tabStatus == e_tab::PRODUCTION_CLICKED) {
					zoom(views[e_views::PRODUCTION], event.mouseWheelScroll.delta, Engine::ZOOM_FACTOR_PRODUCTION);
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
					else if (tabStatus == e_tab::LOGISTICS) {
						logisticsInput(window, views, screenPosition, tiles, tabStatus, event);
					}
					else if (tabStatus == e_tab::OPTIONS) {
						optionsInput(window.mapPixelToCoords(screenPosition, *views[e_views::OPTIONS]));
					}
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					if (tabStatus == e_tab::LOGISTICS_SEND) {
						logisticsInput(window, views, screenPosition, tiles, tabStatus, event);
					}
				}
				break; 
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (tabStatus == e_tab::OPTIONS) {
						if (zoomSensitivity.isClicked()) {
							zoomSensitivity.setClickedOrNot(false, window.mapPixelToCoords(screenPosition, *views[e_views::OPTIONS]));
						}
						if (cameraSensitivity.isClicked()) {
							cameraSensitivity.setClickedOrNot(false, window.mapPixelToCoords(screenPosition, *views[e_views::OPTIONS]));
						}
					}
					else if (tabStatus == e_tab::LOGISTICS) {
						if (selectedLogisticsTile.x != -1) {
							if (tiles[selectedLogisticsTile.x][selectedLogisticsTile.y]->getSelectedEquipment() != "None") {
								if (tiles[selectedLogisticsTile.x][selectedLogisticsTile.y]->getAdjustable().isClicked()) {
									tiles[selectedLogisticsTile.x][selectedLogisticsTile.y]->getAdjustable().setClickedOrNot(false, window.mapPixelToCoords(screenPosition, *views[e_views::LOGISTICS]));
								}
							}
						}
					}
				}
				break;
			case sf::Event::TextEntered:
				if (tabStatus == e_tab::LOGISTICS) {
					logisticsInput(window, views, screenPosition, tiles, tabStatus, event);
				}
				break;
		}
	}

	if (tabStatus == e_tab::UNITS) {
		cameraMover(views[e_views::MAP], sf::Vector2f(mapSize.x, mapSize.y), sf::Vector2f(0, 0));
	}
	else if (tabStatus == e_tab::PRODUCTION) {
		cameraMover(views[e_views::PRODUCTION], sf::Vector2f(mapSize.x, mapSize.y), sf::Vector2f(0, 0));
	}
	else if (tabStatus == e_tab::PRODUCTION_CLICKED) {
		cameraMover(views[e_views::RESEARCH_LEFT], sf::Vector2f(researchBackgroundLeft.getSize().x - resolution.x * 0.2f, researchBackgroundLeft.getSize().y - resolution.y * 0.45f), sf::Vector2f(resolution.x * 0.2f, resolution.y * 0.45f));
		researchFrameLeft.setPosition(views[e_views::RESEARCH_LEFT]->getCenter());
	}
	else if (tabStatus == e_tab::RESEARCH) {
		cameraMover(views[e_views::RESEARCH_LEFT], sf::Vector2f(researchBackgroundLeft.getSize().x - resolution.x * 0.2f, researchBackgroundLeft.getSize().y - resolution.y * 0.45f), sf::Vector2f(resolution.x * 0.2f, resolution.y * 0.45f));
		researchFrameLeft.setPosition(views[e_views::RESEARCH_LEFT]->getCenter());
	}
	else if (tabStatus == e_tab::LOGISTICS) {
		if (selectedLogisticsTile.x == -1) {
			cameraMover(views[e_views::MAP], sf::Vector2f(mapSize.x, mapSize.y), sf::Vector2f(0, 0));
		}
		else if(tiles[selectedLogisticsTile.x][selectedLogisticsTile.y]->getSelectedEquipment() != "None" && tiles[selectedLogisticsTile.x][selectedLogisticsTile.y]->getAdjustable().isClicked()){
			tiles[selectedLogisticsTile.x][selectedLogisticsTile.y]->getAdjustable().setMovablePosition(window.mapPixelToCoords(screenPosition, *views[e_views::LOGISTICS]));
			tiles[selectedLogisticsTile.x][selectedLogisticsTile.y]->setEquipmentNumSelected(int(tiles[selectedLogisticsTile.x][selectedLogisticsTile.y]->getAdjustable().getVal()));
		}
	}
	if (zoomSensitivity.isClicked()) {
		zoomSensitivity.setMovablePosition(window.mapPixelToCoords(screenPosition, *views[e_views::OPTIONS]));
		ZOOM_SENSITIVITY = zoomSensitivity.getVal();
	}
	if (cameraSensitivity.isClicked()) {
		cameraSensitivity.setMovablePosition(window.mapPixelToCoords(screenPosition, *views[e_views::OPTIONS]));
		CAMERA_SENSITIVITY = cameraSensitivity.getVal();
	}
}

void Engine::hudInput(sf::Vector2f mouseHudPos, e_tab& tab)
{
	if (mouseHudPos.y > (resolution.y * 0.05f)) {
		switch (int(mouseHudPos.x / (resolution.x / 6))) {
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

void Engine::researchInput(sf::RenderWindow& window, std::vector<std::shared_ptr<sf::View>>& views, sf::Vector2i mouseLocalPosition)
{
	sf::Vector2f mouseGlobalPosition = window.mapPixelToCoords(mouseLocalPosition, *views[e_views::RESEARCH_LEFT]);
	sf::FloatRect bounds;
	for (auto& res : allResearch) {
		bounds = res.getEquipmentBackground().getGlobalBounds();
		if (bounds.contains(mouseGlobalPosition) && (res.prevResearchVectorLocation == -1 || allResearch[res.prevResearchVectorLocation].isResearched() == e_researchStatus::RESEARCHED)) {
			res.doResearch();
		}
	}
}

void Engine::productionInput(sf::RenderWindow & window, std::vector<std::shared_ptr<sf::View>>& views, sf::Vector2i mouseLocalPosition, e_tab& tabStatus, Tile*** tiles)
{
	if (tabStatus == e_tab::PRODUCTION) {
		sf::Vector2f mouseProductionPosition = window.mapPixelToCoords(mouseLocalPosition, *views[e_views::PRODUCTION]);
		if (mouseProductionPosition.x >= 0 && mouseProductionPosition.x < mapSize.x && mouseProductionPosition.y >= 0 && mouseProductionPosition.y < mapSize.y) {
			productionSelectedTile = withinMapBounds(sf::Vector2i(static_cast<int>(mouseProductionPosition.y / TILE_SIZE), static_cast<int>(mouseProductionPosition.x / TILE_SIZE)));
			if (tiles[productionSelectedTile.x][productionSelectedTile.y]->hasFactory()) {
				tabStatus = e_tab::PRODUCTION_CLICKED;
				views[e_views::PRODUCTION]->setCenter(TILE_SIZE * (productionSelectedTile.y + 0.5f), TILE_SIZE * (productionSelectedTile.x + 0.5f));
			}
			else if (allegiances[playerNum].getConstructionPoints() > 400.f) {
				tiles[productionSelectedTile.x][productionSelectedTile.y]->addFactory();
				allegiances[playerNum].setConstructionPoints(allegiances[playerNum].getConstructionPoints() - 400.f);
			}
		}
	}
	else if (tabStatus == e_tab::PRODUCTION_CLICKED) {
		if (mouseLocalPosition.x < (resolution.x * 0.4f)) {
			sf::Vector2f mouseResPosition = window.mapPixelToCoords(mouseLocalPosition, *views[e_views::RESEARCH_LEFT]);
			sf::FloatRect bounds;
			for (auto& res : allResearch) {
				bounds = res.getEquipmentBackground().getGlobalBounds();
				if (bounds.contains(mouseResPosition) && res.isResearched() == e_researchStatus::RESEARCHED) {
					tiles[productionSelectedTile.x][productionSelectedTile.y]->setEquipmentInProduction(res.getEquipment().getName(),  res.getEquipment().getProductionCost());
					tabStatus = e_tab::PRODUCTION;
					break;
				}
			}
		}
		else {
			sf::Vector2f mouseProductionPosition = window.mapPixelToCoords(mouseLocalPosition, *views[e_views::PRODUCTION]);
			if (mouseProductionPosition.x >= 0 && mouseProductionPosition.x < mapSize.x && mouseProductionPosition.y >= 0 && mouseProductionPosition.y < mapSize.y) {
				productionSelectedTile = sf::Vector2i(static_cast<int>(mouseProductionPosition.x / TILE_SIZE), static_cast<int>(mouseProductionPosition.y / TILE_SIZE));
				if (tiles[productionSelectedTile.x][productionSelectedTile.y]->hasFactory()) {
					tabStatus = e_tab::PRODUCTION_CLICKED;
					views[e_views::PRODUCTION]->setCenter(TILE_SIZE * (productionSelectedTile.x + 0.5f), TILE_SIZE * (productionSelectedTile.y + 0.5f));
				}
			}
		}
	}
}

void Engine::logisticsInput(sf::RenderWindow & window, std::vector<std::shared_ptr<sf::View>>& views, sf::Vector2i mouseLocalPosition, Tile*** tiles, e_tab& tabStatus, sf::Event& event)
{
	if (tabStatus == e_tab::LOGISTICS && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		//If a tile is not currently selected in the Logistics tab, select a tab.
		if (selectedLogisticsTile.x == -1) {
			sf::Vector2f mouseMapPosition = window.mapPixelToCoords(mouseLocalPosition, *views[e_views::MAP]);
			selectedLogisticsTile = withinMapBounds(sf::Vector2i(static_cast<int>(mouseMapPosition.y / TILE_SIZE), static_cast<int>(mouseMapPosition.x / TILE_SIZE)));
		}
		//If a tile is already selected then the equipment minitab is open.
		else {
			sf::Vector2f mouseLogisticsPosition = window.mapPixelToCoords(mouseLocalPosition, *views[e_views::LOGISTICS]);
			//If an equipment is being seelcted to be sent
			if (mouseLogisticsPosition.x > 10 && mouseLogisticsPosition.x < 160) {
				std::unordered_map <std::string, int>& storage = tiles[selectedLogisticsTile.x][selectedLogisticsTile.y]->getStorage();
				//If any of the equipement is chosen.
				if (mouseLogisticsPosition.y > 10 && mouseLogisticsPosition.y < storage.size() * 35 + 5) {
					if (fmod(mouseLogisticsPosition.y - 10, 35) < 30.f) {
						int i = 0;
						std::unordered_map <std::string, int>::iterator selected;
						for (selected = storage.begin(); selected != storage.end(); selected++) {
							if (i == static_cast<int>((mouseLogisticsPosition.y - 10) / 35)) {
								//Select an Equipment to send.
								tiles[selectedLogisticsTile.x][selectedLogisticsTile.y]->setSelectedEquipment(selected->first);
								tiles[selectedLogisticsTile.x][selectedLogisticsTile.y]->setEquipmentNumSelected(0);
								break;
							}
							i++;
						}
					}
				}
			}
			else {
				auto& tempAdj = tiles[selectedLogisticsTile.x][selectedLogisticsTile.y]->getAdjustable();
				//Exit the equipment minitab and deselect the tile.
				if (exitButton.getGlobalBounds().contains(mouseLogisticsPosition)) {
					tiles[selectedLogisticsTile.x][selectedLogisticsTile.y]->setEquipmentNumSelected(0);
					selectedLogisticsTile.x = -1;
				}
				//Send the equipment currently chosen with the user set amount and priority.
				else if (sendButtonBackground.getGlobalBounds().contains(mouseLogisticsPosition)) {
					if (tiles[selectedLogisticsTile.x][selectedLogisticsTile.y]->initializeTransportable()) {
						tabStatus = e_tab::LOGISTICS_SEND;
					}
				}
				//Set the amount of equipment to send+
				else if (tempAdj.movableContains(mouseLogisticsPosition)) {
					if (!tempAdj.isClicked()) {
						tempAdj.setClickedOrNot(true, mouseLogisticsPosition);
					}
				}
				else if (selectedLogisticsTile.x != -1) {
					Writable& priorityGetter = tiles[selectedLogisticsTile.x][selectedLogisticsTile.y]->getPriorityGetter();
					priorityGetter.setClicked(mouseLogisticsPosition);
				}
			}
		}
	}
	else if(tabStatus == e_tab::LOGISTICS_SEND && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right){
		sf::Vector2f mouseMapPosition = window.mapPixelToCoords(mouseLocalPosition, *views[e_views::MAP]);
		sf::Vector2i toSend = withinMapBounds(sf::Vector2i(static_cast<int>(mouseMapPosition.y / TILE_SIZE), static_cast<int>(mouseMapPosition.x / TILE_SIZE)));
		if (toSend.x > -1) {
			tiles[selectedLogisticsTile.x][selectedLogisticsTile.y]->addPathToTPinLoadingBay(toSend);
			tiles[selectedLogisticsTile.x][selectedLogisticsTile.y]->launchTransportable();
		}
		tabStatus = e_tab::LOGISTICS;
		selectedLogisticsTile.x = -1;
	}
	else if (selectedLogisticsTile.x != -1 && event.type == sf::Event::TextEntered) {
		Writable& priorityGetter = tiles[selectedLogisticsTile.x][selectedLogisticsTile.y]->getPriorityGetter();
		if (priorityGetter.isClicked()) {
			priorityGetter.addNumber(event.text.unicode);
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
}

void Engine::zoom(std::shared_ptr<sf::View> mapView, float scrollDelta, float& zoomFactor)
{
	if (zoomFactor < MAX_ZOOM && scrollDelta > 0) {
		zoomFactor += ZOOM_SENSITIVITY;
		if (zoomFactor > MAX_ZOOM)zoomFactor = MAX_ZOOM;
		mapView->setSize(resolution.x * zoomFactor, resolution.y * 0.9 * zoomFactor);
	}
	else if (zoomFactor > MIN_ZOOM && scrollDelta < 0) {
		zoomFactor -= ZOOM_SENSITIVITY;
		if (zoomFactor < MIN_ZOOM)zoomFactor = MIN_ZOOM;
		mapView->setSize(resolution.x * zoomFactor, resolution.y * 0.9 * zoomFactor);
	}
}

void Engine::cameraMover(std::shared_ptr<sf::View> view, sf::Vector2f boundsMax, sf::Vector2f boundsMin)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && view->getCenter().y > (CAMERA_SENSITIVITY + boundsMin.y)) {
		view->setCenter(sf::Vector2f(view->getCenter().x, view->getCenter().y - CAMERA_SENSITIVITY));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && view->getCenter().y < (boundsMax.y - CAMERA_SENSITIVITY)) {
		view->setCenter(sf::Vector2f(view->getCenter().x, view->getCenter().y + CAMERA_SENSITIVITY));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && view->getCenter().x > (CAMERA_SENSITIVITY + boundsMin.x)) {
		view->setCenter(sf::Vector2f(view->getCenter().x - CAMERA_SENSITIVITY, view->getCenter().y));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && view->getCenter().x < (boundsMax.x - CAMERA_SENSITIVITY)) {
		view->setCenter(sf::Vector2f(view->getCenter().x + CAMERA_SENSITIVITY, view->getCenter().y));
	}
}

void Engine::run()
{
	//start
    Tile*** tiles = saveLoader(allegiances);

	mapSize = sf::Vector2f(tilesNums.y * TILE_SIZE, tilesNums.x * TILE_SIZE);
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
	window.setFramerateLimit(60);

	//Views (don't mess with the push_back order)
	std::vector<std::shared_ptr<sf::View>> views;
	views.reserve(9);
	//HUD view
	views[0] = std::make_shared<sf::View>(sf::FloatRect(0, 0, resolution.x, resolution.y * 0.1f));
	views[0]->setViewport(sf::FloatRect(0, 0, 1, 0.1f));
	//Map view
	views[1] = std::make_shared<sf::View>(sf::Vector2f(mapSize.x / 2, mapSize.y / 2), sf::Vector2f(resolution.x, resolution.y * 0.9f));
	views[1]->setViewport(sf::FloatRect(0, 0.1f, 1, 0.9f));
	//Research left view
	views[2] = std::make_shared<sf::View>(sf::FloatRect(0, 0, resolution.x * 0.4f, resolution.y * 0.9f));
	views[2]->setViewport(sf::FloatRect(0.f, 0.1f, 0.4f, 0.9f));
	//Research right view
	views[3] = std::make_shared<sf::View>(sf::FloatRect(0, 0, resolution.x * 0.1f, resolution.y * 0.9f));
	views[3]->setViewport(sf::FloatRect(0.9f, 0.1f, 0.1f, 0.9f));
	//Production view
	views[4] = std::make_shared<sf::View>(sf::Vector2f(mapSize.x / 2, mapSize.y / 2), sf::Vector2f(resolution.x, resolution.y * 0.9f));
	views[4]->setViewport(sf::FloatRect(0, 0.1f, 1, 0.9f));
	//Logistics view
	views[5] = std::make_shared<sf::View>(sf::Vector2f(resolution.x / 4, resolution.y * 0.225f), sf::Vector2f(resolution.x / 2, resolution.y * 0.45f));
	views[5]->setViewport(sf::FloatRect(0.25f, 0.325f, 0.5f, 0.45f));
	//Building view
	views[6] = std::make_shared<sf::View>(sf::Vector2f(mapSize.x / 2, mapSize.y / 2), sf::Vector2f(resolution.x, resolution.y * 0.9f));
	views[6]->setViewport(sf::FloatRect(0, 0.1f, 1, 0.9f));
	//Options view
	views[7] = std::make_shared<sf::View>(sf::Vector2f(resolution.x / 4, resolution.y * 0.225f), sf::Vector2f(resolution.x / 2, resolution.y * 0.45f));
	views[7]->setViewport(sf::FloatRect(0.25f, 0.325f, 0.5f, 0.45f));
	//Equipment view
	views[8] = std::make_shared<sf::View>(sf::FloatRect(0, 0, resolution.x * 0.1f, resolution.y * 0.9f));
	views[8]->setViewport(sf::FloatRect(0.9f, 0.1f, 0.1f, 0.9f));

	//Tab status
	e_tab tabStatus = e_tab::UNITS;

	//Setting stats for equipments
	equipmentStatSetter();

	//Runtime clock
	sf::Clock clock; 
	int newHours;
	float deltaTime;

	while (window.isOpen()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
		}
		else {
			deltaTime = clock.restart().asSeconds();
			if (deltaTime < 0.01) {
				std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>((0.01 - deltaTime) * 100000)));
			}
			newHours = handleTime(hours, deltaTime + clock.restart().asSeconds());
			//updating the tiles and the two sides-allegiances
			for (int i = 0; i < 2; i++) {
				if(newHours > 0)allegiances[i].update(newHours, tiles);
			}
			//updating the research
			for (auto& res : allResearch) {
				if (res.isResearched() == e_researchStatus::IN_PROGRESS && newHours > 0)res.update(newHours);
			}
			allegianceText1.setString(allegiances[0].getName() + " CP: " + std::to_string(static_cast<int>(allegiances[0].getConstructionPoints())));
			allegianceText2.setString(allegiances[1].getName() + " CP: " + std::to_string(static_cast<int>(allegiances[1].getConstructionPoints())));
			input(window, views, resolution, tabStatus, tiles);
			drawToWindow(window, views, tabStatus, tiles);
			window.display();
			window.clear();
		}
	}
	for (int i = 0; i < tilesNums.x; i++) {
		for (int j = 0; j < tilesNums.y; j++) {
			delete tiles[i][j];
		}
		delete[] tiles[i];
	}
	delete[] tiles;
}
