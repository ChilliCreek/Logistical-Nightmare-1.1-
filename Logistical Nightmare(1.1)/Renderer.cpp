#include "pch.h"
#include "Renderer.h"

#define PI 3.14159265

//initialization of static variables
const float Renderer::TIME_DILATION = 2500.f;
float Renderer::ZOOM_SENSITIVITY = 0.05f;
int Renderer::GAME_SPEED = 4;
sf::Font Renderer::font;
sf::Vector2f Renderer::resolution;
std::string Renderer::monthStrings[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

Renderer::Renderer()
{
	//resolution 
	resolution.x = sf::VideoMode::getDesktopMode().width;
	resolution.y = sf::VideoMode::getDesktopMode().height;
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
	//font set
	font.loadFromFile("font/Stanberry.ttf");
	//Allegiance names
	allegianceText1.setFont(font);
	allegianceText2.setFont(font);
	allegianceText1.setCharacterSize(25);
	allegianceText2.setCharacterSize(25);
	allegianceText1.setPosition(10, 10);
	allegianceText2.setPosition(resolution.x * 0.85f, 10);
	//Tabs
	sf::Color gold(255, 223, 0, 255);
	tabTexts[0].setString("Map");
	tabTexts[1].setString("Research");
	tabTexts[2].setString("Production");
	tabTexts[3].setString("Logistics");
	tabTexts[4].setString("Building");
	tabTexts[5].setString("Options");
	for (int i = 0; i < 6; i++) {
		tabTexts[i].setFillColor(sf::Color::Blue);
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
}

void Renderer::drawToWindow(sf::RenderWindow& window, std::vector<sf::View>& views, e_tab& tabs, std::vector <std::vector <Tile> >& tiles)
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
	case e_tab::LOGISTICS:
		break;
	case e_tab::BUILDING:
		break;
	case e_tab::OPTIONS:
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
	timeAndDate.setString(Renderer::secondsToDateAndTime(runTime));
	window.draw(timeAndDate);
}

void Renderer::drawMapToWindow(sf::RenderWindow& window, sf::View& mapView, std::vector <std::vector <Tile> >& tiles)
{
	window.setView(mapView);
	window.draw(mapBackground);
	for (int i = 0; i < tilesNums.x; i++) {
		for (int j = 0; j < tilesNums.y; j++) {
			window.draw(tiles[i][j].getTileSprite());
			if (tiles[i][j].hasFactory())window.draw(tiles[i][j].getFactorySprite());
			window.draw(tiles[i][j].getTerrainSprite());
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

void Renderer::drawResearchLeftToWindow(sf::RenderWindow& window, std::vector<sf::View>& views)
{
	window.setView(views[static_cast<int>(e_views::RESEARCH_LEFT)]);
	window.draw(researchBackgroundLeft);
	sf::RectangleShape arrow;
	arrow.setFillColor(sf::Color::Black);
	for (auto& res : allResearch) {
		if (res.prevResearchVectorLocation != -1) {
			arrow.setSize(sf::Vector2f(std::sqrt(std::powf(allResearch[res.prevResearchVectorLocation].getEquipmentBackground().getGlobalBounds().top - res.getEquipmentBackground().getGlobalBounds().top, 2) + std::powf(allResearch[res.prevResearchVectorLocation].getEquipmentBackground().getGlobalBounds().left - res.getEquipmentBackground().getGlobalBounds().left, 2)), 5.f));
			arrow.setPosition(res.getEquipmentBackground().getGlobalBounds().left + res.getEquipmentBackground().getGlobalBounds().width / 2, res.getEquipmentBackground().getGlobalBounds().top + res.getEquipmentBackground().getGlobalBounds().height / 2);
			arrow.setRotation(90 - std::atan2f(allResearch[res.prevResearchVectorLocation].getEquipmentBackground().getGlobalBounds().left - res.getEquipmentBackground().getGlobalBounds().left, allResearch[res.prevResearchVectorLocation].getEquipmentBackground().getGlobalBounds().top - res.getEquipmentBackground().getGlobalBounds().top) * 180 / PI);
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

void Renderer::drawOptionsToWindow(sf::RenderWindow & window, std::vector<sf::View>& views)
{

}

void Renderer::drawProductionToWindow(sf::RenderWindow& window, std::vector<sf::View>& views, std::vector<std::vector<Tile>>& tiles, e_tab& tabs)
{
	window.setView(views[static_cast<int>(e_views::PRODUCTION)]);
	window.draw(mapBackground);
	for (int i = 0; i < tilesNums.x; i++) {
		for (int j = 0; j < tilesNums.y; j++) {
			window.draw(tiles[i][j].getTileSprite());
			if (tiles[i][j].hasFactory()) {
				window.draw(tiles[i][j].getFactorySprite());
				window.draw(tiles[i][j].getBeingProduced());
			}
		}
	}
	if (tabs == e_tab::PRODUCTION_CLICKED) {
		drawResearchLeftToWindow(window, views);
	}
}

std::string Renderer::secondsToDateAndTime(float sec)
{
	e_tab res = e_tab(1);
	sec = sec * TIME_DILATION;
	float days = (sec / 86400.f);
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
			addedOne = (days > 31.f);
			days = addedOne ? (days - 31.f) : days;
			month = addedOne ? (month + 1) : month;
			break;
		case 2:
			if (year % 4 == 0) {
				addedOne = (days > 29.f);
				days = addedOne ? (days - 29.f) : days;
				month = addedOne ? (month + 1) : month;
				break;
			}
			else {
				addedOne = (days > 28.f);
				days = addedOne ? (days - 28.f) : days;
				month = addedOne ? (month + 1) : month;
				break;
			}
		case 3:
			addedOne = (days > 31.f);
			days = addedOne ? (days - 31.f) : days;
			month = addedOne ? (month + 1) : month;
			break;
		case 4:
			addedOne = (days > 30.f);
			days = addedOne ? (days - 30.f) : days;
			month = addedOne ? (month + 1) : month;
			break;
		case 5:
			addedOne = (days > 31.f);
			days = addedOne ? (days - 31.f) : days;
			month = addedOne ? (month + 1) : month;
			break;
		case 6:
			addedOne = (days > 30.f);
			days = addedOne ? (days - 30.f) : days;
			month = addedOne ? (month + 1) : month;
			break;
		case 7:
			addedOne = (days > 31.f);
			days = addedOne ? (days - 31.f) : days;
			month = addedOne ? (month + 1) : month;
			break;
		case 8:
			addedOne = (days > 31.f);
			days = addedOne ? (days - 31.f) : days;
			month = addedOne ? (month + 1) : month;
			break;
		case 9:
			addedOne = (days > 30.f);
			days = addedOne ? (days - 30.f) : days;
			month = addedOne ? (month + 1) : month;
			break;
		case 10:
			addedOne = (days > 31.f);
			days = addedOne ? (days - 31.f) : days;
			month = addedOne ? (month + 1) : month;
			break;
		case 11:
			addedOne = (days > 30.f);
			days = addedOne ? (days - 30.f) : days;
			month = addedOne ? (month + 1) : month;
			break;
		case 12:
			addedOne = (days > 31.f);
			days = addedOne ? (days - 31.f) : days;
			month = addedOne ? (month + 1) : month;
			break;
		}
	}
	int hours = (days - float(int(days))) / (1.f / 24.f);
	ss << monthStrings[month - 1] << " " << int(days) + 1 << " " << (year + 1940) << "  " << hours << ":00";
	return ss.str();
}