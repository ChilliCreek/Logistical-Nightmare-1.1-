#include "pch.h"
#include "Renderer.h"

//initialization of static variables
float Renderer::ZOOM_SENSITIVITY = 0.05f;
int Renderer::GAME_SPEED = 4;
int Renderer::playerNum = 0;
sf::Font Renderer::font;
std::string Renderer::monthStrings[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
//resolution 
sf::Vector2f Renderer::resolution = sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
Renderer::Renderer() : zoomSensitivity(sf::Vector2f(0, 0), 0.01f, 0.10f, resolution.x * 0.3f, "Zoom Sensitivity:", 0.05f, font), cameraSensitivity(sf::Vector2f(0, 100), 5.f, 30.f, resolution.x * 0.3f, "Camera Sensitivity:", 15.f, font), allegiances(2), selectedLogisticsTile(-1, -1), exitButton(sf::Vector2f(10, 10))
{
	allResearch.reserve(11);
	//exit button
	exitButton.setFillColor(sf::Color::Red);
	exitButton.setOutlineColor(sf::Color::Red);
	exitButton.setOutlineThickness(-1);
	//hud background
	hudBackground.setFillColor(sf::Color::Black);
	hudBackground.setPosition(0, 0);
	hudBackground.setSize(sf::Vector2f(resolution.x, resolution.y * 0.1f));
	//research background
	sf::Color vwSatinSilver(182, 194, 204);
	researchBackgroundLeft.setFillColor(vwSatinSilver);
	researchBackgroundLeft.setPosition(0, 0);
	researchBackgroundLeft.setSize(sf::Vector2f(2000.f,1200.f));
	sf::Color chryslerDarkSilver(104, 112, 124);
	researchBackgroundRight.setFillColor(chryslerDarkSilver);
	researchBackgroundRight.setPosition(0, 0);
	researchBackgroundRight.setSize(sf::Vector2f(resolution.x * 0.1f, resolution.y * 0.9f));
	researchBackgroundRight.setOutlineColor(sf::Color::Black);
	researchBackgroundRight.setOutlineThickness(-2);
	//Research windows' frames
	researchFrameLeft.setOutlineColor(sf::Color::Black);
	researchFrameLeft.setOutlineThickness(-5);
	researchFrameLeft.setSize(sf::Vector2f(resolution.x * 0.4f, resolution.y * 0.9f));
	researchFrameLeft.setOrigin(sf::Vector2f(resolution.x * 0.2f, resolution.y * 0.45f));
	researchFrameLeft.setPosition(sf::Vector2f(resolution.x * 0.2f, resolution.y * 0.45f));
	researchFrameLeft.setFillColor(sf::Color(0, 0, 0, 0));
	//blue map background
	sf::Color seaBlue(0, 105, 248);
	mapBackground.setFillColor(seaBlue);
	//HUD:
	//Allegiance names
	allegianceText1.setFont(font);
	allegianceText2.setFont(font);
	allegianceText1.setCharacterSize(25);
	allegianceText2.setCharacterSize(25);
	allegianceText1.setPosition(10, 10);
	allegianceText2.setPosition(resolution.x * 0.85f, 10);
	//Tabs
	tabTexts[0].setString("Map");
	tabTexts[1].setString("Research");
	tabTexts[2].setString("Production");
	tabTexts[3].setString("Logistics");
	tabTexts[4].setString("Building");
	tabTexts[5].setString("Options");
	for (int i = 0; i < 6; i++) {
		tabTexts[i].setFillColor(sf::Color::Black);
		tabTexts[i].setCharacterSize(20);
		tabTexts[i].setPosition((resolution.x / 6.f) * i + resolution.x / 12.f, resolution.y * 0.075f);
		tabTexts[i].setFont(font);
		tabTexts[i].setOrigin(tabTexts[i].getLocalBounds().width / 2, tabTexts[i].getLocalBounds().height / 2);
	}
	for (int i = 0; i < 6; i++) {
		tabButtons[i].setTexture(TextureHolder::getTexture("graphics/tab_button.png"));
		tabButtons[i].setPosition((resolution.x / 6.f) * i + resolution.x / 12.f, resolution.y * 0.075f);
		tabButtons[i].setOrigin(tabButtons[i].getLocalBounds().width / 2, tabButtons[i].getLocalBounds().height / 2);
	}
	//runTime
	timeAndDate.setCharacterSize(20);
	timeAndDate.setFont(font);
	timeAndDate.setPosition(resolution.x * 0.25f, 0);
	//Set game speed
	speedButtons.setTexture(TextureHolder::getTexture("graphics/speed_bar.png"));
	speedButtons.setPosition(resolution.x * 0.4f, 5);
	speedButtons.setScale(0.4f, 0.4f);
	//Game speed buttons shading
	gameSpeedButtonShade.setSize(sf::Vector2f(speedButtons.getLocalBounds().width / 5, speedButtons.getLocalBounds().height));
	gameSpeedButtonShade.setFillColor(sf::Color(255, 255, 255, 96));
	gameSpeedButtonShade.setScale(0.4f, 0.4f);
	gameSpeedButtonShade.setPosition(resolution.x * 0.4f + speedButtons.getLocalBounds().width * 0.6f * 0.4f, speedButtons.getGlobalBounds().top);
	//Logistics:
	sendButtonBackground.setPosition(200, 80);
	sendButtonBackground.setSize(sf::Vector2f(60, 30));
	sendButtonBackground.setFillColor(sf::Color::White);
	sendButton.setFont(font);
	sendButton.setCharacterSize(25);
	sendButton.setPosition(200, 80);
	sendButton.setString("Send");
	sendButton.setFillColor(sf::Color::Black);
	//Options:
	optionsBackground.setPosition(0, 0);
	optionsBackground.setSize(sf::Vector2f(resolution.x * 0.5f, resolution.y * 0.45f));
	optionsBackground.setFillColor(chryslerDarkSilver);
	optionsBackground.setOutlineThickness(2);
	optionsBackground.setOutlineColor(sf::Color::Black);
}

void Renderer::drawToWindow(sf::RenderWindow& window, std::vector<sf::View>& views, e_tab& tabs, Tile*** tiles)
{
	drawHudToWindow(window, views[static_cast<int>(e_views::HUD)]);
	switch (tabs) {
	case e_tab::UNITS:
		drawMapToWindow(window, views[static_cast<int>(e_views::MAP)], tiles);
		break;
	case e_tab::RESEARCH:
		drawMapToWindow(window, views[static_cast<int>(e_views::MAP)], tiles);
		drawResearchLeftToWindow(window, views);
		drawResearchRightToWindow(window, views);
		break;
	case e_tab::PRODUCTION_CLICKED:
	case e_tab::PRODUCTION:
		drawProductionToWindow(window, views, tiles, tabs);
		break;
	case e_tab::LOGISTICS_SEND:
	case e_tab::LOGISTICS:
		drawMapToWindow(window, views[static_cast<int>(e_views::MAP)], tiles);
		drawLogisticsToWindow(window, views, tabs, tiles);
		break;
	case e_tab::BUILDING:
		break;
	case e_tab::OPTIONS:
		drawOptionsToWindow(window, views[static_cast<int>(e_views::OPTIONS)]);
		break;
	}
}

void Renderer::drawHudToWindow(sf::RenderWindow& window, sf::View& hudView)
{
	window.setView(hudView);
	window.draw(hudBackground);
	window.draw(allegianceText1);
	window.draw(allegianceText2);
	window.draw(speedButtons);
	window.draw(gameSpeedButtonShade);
	for (int i = 0; i < 6; i++) {
		window.draw(tabButtons[i]);
	}
	for (int i = 0; i < 6; i++) {
		window.draw(tabTexts[i]);
	}
	timeAndDate.setString(Renderer::hoursToDateAndTime(hours));
	window.draw(timeAndDate);
}

void Renderer::drawMapToWindow(sf::RenderWindow& window, sf::View& mapView, Tile*** tiles)
{
	window.setView(mapView);
	window.draw(mapBackground);
	for (int i = 0; i < tilesNums.x; i++) {
		for (int j = 0; j < tilesNums.y; j++) {
			tiles[i][j]->drawItselfOnMap(window, mapView);
		}
	}
}

void Renderer::drawResearchRightToWindow(sf::RenderWindow& window, std::vector<sf::View>& views)
{
	window.setView(views[static_cast<int>(e_views::RESEARCH_RIGHT)]);
	window.draw(researchBackgroundRight);
	int i = 0;
	for (auto& res : allResearch) {
		if (res.isResearched() == e_researchStatus::IN_PROGRESS) {
			sf::RectangleShape recEquipmentBackground = res.getEquipmentBackground();
			recEquipmentBackground.setPosition(0, recEquipmentBackground.getLocalBounds().height * i);
			sf::RectangleShape recProgressBarFull = res.getProgressBarFull();
			recProgressBarFull.setPosition(0, recEquipmentBackground.getLocalBounds().height * i);
			sf::RectangleShape recProgressBarLeft = res.getProgressBarLeft();
			recProgressBarLeft.setPosition(0, recEquipmentBackground.getLocalBounds().height * i);
			sf::Sprite resSprite = res.getEquipment().getEquipmentSprite();
			resSprite.setPosition(0, recEquipmentBackground.getLocalBounds().height * i);
			window.draw(recEquipmentBackground);
			window.draw(resSprite);
			window.draw(recProgressBarFull);
			window.draw(recProgressBarLeft);
			i++;
		}
	}
}

void Renderer::drawLogisticsToWindow(sf::RenderWindow & window, std::vector<sf::View>& views, e_tab& tabs, Tile*** tiles)
{
	if (tabs == e_tab::LOGISTICS) {
		if (selectedLogisticsTile.x != -1) {
			window.setView(views[static_cast<int>(e_views::LOGISTICS)]);
			window.draw(optionsBackground);
			exitButton.setPosition(0, 0);
			window.draw(exitButton);
			tiles[selectedLogisticsTile.x][selectedLogisticsTile.y]->drawItselfOnLogistics(window, views[static_cast<int>(e_views::LOGISTICS)]);
			if (tiles[selectedLogisticsTile.x][selectedLogisticsTile.y]->getSelectedEquipment() != "None") {
				window.draw(sendButtonBackground);
				window.draw(sendButton);
			}
		}
	}
	else if(tabs == e_tab::LOGISTICS_SEND){
		window.setView(views[static_cast<int>(e_views::LOGISTICS)]);
		auto tilePaths = tiles[selectedLogisticsTile.x][selectedLogisticsTile.y]->getTransPInLoadingBay().pt->getPaths();
		sf::RectangleShape arrows; sf::RectangleShape outline;
		outline.setPosition(selectedLogisticsTile.x * TILE_SIZE, selectedLogisticsTile.y * TILE_SIZE);
		outline.setFillColor(sf::Color(0, 0, 0, 0));
		outline.setOutlineColor(sf::Color::Blue);
		outline.setOutlineThickness(-5);
		window.draw(outline);
		arrows.setFillColor(sf::Color::Black);
		for (auto const& [prev, path] : tilePaths) {
			arrows.setRotation(std::atan2f(prev.y - path.y, prev.x - path.x));
			arrows.setPosition(prev.x * TILE_SIZE, prev.y * TILE_SIZE);
			arrows.setSize(sf::Vector2f(distanceBetween2DPoints(prev.x * TILE_SIZE, prev.y * TILE_SIZE, path.x * TILE_SIZE, path.y * TILE_SIZE), 5));
			window.draw(arrows);
		}
	}
}

void Renderer::drawResearchLeftToWindow(sf::RenderWindow& window, std::vector<sf::View>& views)
{
	window.setView(views[static_cast<int>(e_views::RESEARCH_LEFT)]);
	window.draw(researchBackgroundLeft);
	sf::RectangleShape arrow;
	arrow.setFillColor(sf::Color::Black);
	for (auto& res : allResearch) {
		if (res.prevResearchVectorLocation != -1) {
			arrow.setSize(sf::Vector2f(distanceBetween2DPoints(allResearch[res.prevResearchVectorLocation].getEquipmentBackground().getGlobalBounds().left, allResearch[res.prevResearchVectorLocation].getEquipmentBackground().getGlobalBounds().top, res.getEquipmentBackground().getGlobalBounds().left, res.getEquipmentBackground().getGlobalBounds().top), 5.f));
			arrow.setPosition(res.getEquipmentBackground().getGlobalBounds().left + res.getEquipmentBackground().getGlobalBounds().width / 2, res.getEquipmentBackground().getGlobalBounds().top + res.getEquipmentBackground().getGlobalBounds().height / 2);
			arrow.setRotation(std::atan2f(allResearch[res.prevResearchVectorLocation].getEquipmentBackground().getGlobalBounds().top - res.getEquipmentBackground().getGlobalBounds().top, allResearch[res.prevResearchVectorLocation].getEquipmentBackground().getGlobalBounds().left - res.getEquipmentBackground().getGlobalBounds().left) * 180 / PI);
			window.draw(arrow);
		}
	}
	for (auto& res : allResearch) {
		window.draw(res.getEquipmentBackground());
		window.draw(res.getEquipment().getEquipmentSprite());
		window.draw(res.getResTimeText());
	}
	window.draw(researchFrameLeft);
}

void Renderer::drawOptionsToWindow(sf::RenderWindow & window, sf::View& optionsView)
{
	window.setView(optionsView);
	window.draw(optionsBackground);
	zoomSensitivity.drawItself(window, optionsView);
	cameraSensitivity.drawItself(window, optionsView);
}

void Renderer::drawProductionToWindow(sf::RenderWindow& window, std::vector<sf::View>& views, Tile*** tiles, e_tab& tabs)
{
	window.setView(views[static_cast<int>(e_views::PRODUCTION)]);
	window.draw(mapBackground);
	for (int i = 0; i < tilesNums.x; i++) {
		for (int j = 0; j < tilesNums.y; j++) {
			tiles[i][j]->drawItselfOnProduction(window, views[static_cast<int>(e_views::PRODUCTION)]);
		}
	}
	if (tabs == e_tab::PRODUCTION_CLICKED) {
		drawResearchLeftToWindow(window, views);
	}
	window.setView(views[static_cast<int>(e_views::EQUIPMENT)]);
	window.draw(researchBackgroundRight);
	
	Allegiance& player = allegiances[playerNum];
	sf::Text disp;
	disp.setFont(Renderer::font);
	disp.setCharacterSize(16);

	auto& equipmentList = player.getEquipmentStorage();

	int pos = 0;
	for (const auto& p : equipmentList) {
		disp.setString(p.first + " " + std::to_string(p.second));
		disp.setPosition(10, pos * 30);
		window.draw(disp);
		pos++;
	}
}

std::string Renderer::hoursToDateAndTime(int hours)
{
	int days = hours / 24;
	hours = hours % 24;
	int year = 1;
	std::stringstream ss;

	while ((year % 4 != 0 && days >= 365) || (year % 4 == 0 && days >= 366)) {
		days -= 365;
		days = (year % 4 == 0) ? (days - 1) : days;
		year++;
	}

	int month = 1;
	bool addedOne = true;
	while (addedOne) {
		switch (month) {
		case 1:
			addedOne = (days > 31);
			days = addedOne ? (days - 31) : days;
			month = addedOne ? (month + 1) : month;
			break;
		case 2:
			if (year % 4 == 0) {
				addedOne = (days > 29);
				days = addedOne ? (days - 29) : days;
				month = addedOne ? (month + 1) : month;
				break;
			}
			else {
				addedOne = (days > 28);
				days = addedOne ? (days - 28) : days;
				month = addedOne ? (month + 1) : month;
				break;
			}
		case 3:
			addedOne = (days > 31);
			days = addedOne ? (days - 31) : days;
			month = addedOne ? (month + 1) : month;
			break;
		case 4:
			addedOne = (days > 30);
			days = addedOne ? (days - 30) : days;
			month = addedOne ? (month + 1) : month;
			break;
		case 5:
			addedOne = (days > 31);
			days = addedOne ? (days - 31) : days;
			month = addedOne ? (month + 1) : month;
			break;
		case 6:
			addedOne = (days > 30);
			days = addedOne ? (days - 30) : days;
			month = addedOne ? (month + 1) : month;
			break;
		case 7:
			addedOne = (days > 31);
			days = addedOne ? (days - 31) : days;
			month = addedOne ? (month + 1) : month;
			break;
		case 8:
			addedOne = (days > 31);
			days = addedOne ? (days - 31) : days;
			month = addedOne ? (month + 1) : month;
			break;
		case 9:
			addedOne = (days > 30);
			days = addedOne ? (days - 30) : days;
			month = addedOne ? (month + 1) : month;
			break;
		case 10:
			addedOne = (days > 31);
			days = addedOne ? (days - 31) : days;
			month = addedOne ? (month + 1) : month;
			break;
		case 11:
			addedOne = (days > 30);
			days = addedOne ? (days - 30) : days;
			month = addedOne ? (month + 1) : month;
			break;
		case 12:
			addedOne = (days > 31);
			days = addedOne ? (days - 31) : days;
			month = addedOne ? (month + 1) : month;
			break;
		}
	}
	ss << monthStrings[month - 1] << " " << days << " " << (year + 1940) << "  " << hours << ":00";
	return ss.str();
}
