#include"pch.h"
#include"Tile.h"
#include"Renderer.h"
#include<iostream>
Tile::Tile(int terrain, sf::Vector2i pos, int playerNum) : m_tileNum(pos), m_equipmentNumSelector(sf::Vector2f(200, 50), 0, 0, 120.f, "To send:", 0, Renderer::font), m_playerNum(playerNum), m_priorityGetter(sf::Vector2f(20, 30), sf::Vector2f(300, 100), Renderer::font)
{
	m_beingProduced.setPosition(Renderer::TILE_SIZE * pos.y, Renderer::TILE_SIZE * pos.x + Renderer::TILE_SIZE / 2);
	m_beingProduced.setScale(0.25f, 0.25f);

	m_terrainSprite.setPosition(Renderer::TILE_SIZE * pos.y + 2, Renderer::TILE_SIZE * pos.x + Renderer::TILE_SIZE / 2);
	m_terrainSprite.setTexture(TextureHolder::getTexture("graphics/" + terrainNumToString(terrain) + ".png"));
	m_terrainSprite.setScale(0.49f, 0.49f);

	m_factorySprite.setPosition(Renderer::TILE_SIZE * pos.y, Renderer::TILE_SIZE * pos.x);
	m_factorySprite.setTexture(TextureHolder::getTexture("graphics/factory.png"));
	m_factorySprite.setScale(0.5f, 0.5f);

	m_tileRec.setPosition(Renderer::TILE_SIZE * pos.y, Renderer::TILE_SIZE * pos.x);
	m_tileRec.setSize(sf::Vector2f(200, 200));
	m_tileRec.setTexture(&TextureHolder::getTexture("graphics/map_background.png"));
	m_tileRec.setOutlineColor(sf::Color::Black);
	m_tileRec.setOutlineThickness(2);

	m_equipmentBackground.setPosition(10, 10);
	m_equipmentBackground.setSize(sf::Vector2f(150, 30));
	m_equipmentBackground.setFillColor(sf::Color::White);
	m_equipmentBackground.setOutlineThickness(-1);
	m_equipmentBackground.setOutlineColor(sf::Color::Black);

	m_terrain = terrain;
	m_hasFactory = false;
	m_inProduction = "ConstructionPoints";

	m_inLoadingBay = nullptr;
}

bool Tile::hasFactory() const
{
	return m_hasFactory;
}

void Tile::addFactory()
{
	m_beingProduced.setTexture(TextureHolder::getTexture("graphics/ConstructionPoints.png"));
	m_hasFactory = true;
}

void Tile::setEquipmentInProduction(const std::string& equipmentName, float productionCost)
{
	m_productionCost = productionCost;
	m_beingProduced.setTexture(TextureHolder::getTexture(equipmentName));
	m_inProduction = equipmentName.substr(9, equipmentName.length() - 13);
}

std::pair <std::string, int> Tile::produce(int elapsedHours)
{
	m_produced += elapsedHours * (m_factoryOutput / m_productionCost);
	int latestBatch = int(m_produced) - m_producedBefore;
	m_producedBefore = int(m_produced);
	if (m_inProduction != "ConstructionPoints") {
		m_storage[m_inProduction] += latestBatch;
	}
	std::pair<std::string, int> result = make_pair(m_inProduction, latestBatch);
	return result;
}

void Tile::update(Tile*** tiles, int elapsedHours)
{
	m_transportCapacityInWeight = elapsedHours * DEFAULT_TRANSPORT_CAPACITY_IN_WEIGHT;
	sf::Vector2i theTileToSend;
	int numSent;

	while (!sender.empty() && m_transportCapacityInWeight > 0) {
		try {
			theTileToSend = sender.top().pt->getNextTile(m_tileNum);
			numSent = sender.top().pt->update(m_transportCapacityInWeight, m_tileNum);
			m_transportCapacityInWeight -= numSent;
			tiles[theTileToSend.x][theTileToSend.y]->addTransportableToSender(sender.top());
		}
		catch (const std::invalid_argument&) {
			numSent = sender.top().pt->updateNoNextTile(m_transportCapacityInWeight, m_tileNum);
			if (m_storage.find(sender.top().pt->getName()) != m_storage.end()) {
				m_storage[sender.top().pt->getName()] += numSent;
			}
			else {
				m_storage[sender.top().pt->getName()] = numSent;
			}
			m_transportCapacityInWeight -= numSent;
		}
		if (sender.top().pt->finished(m_tileNum)) {
			sender.pop();
		}
	}
}

std::string Tile::terrainNumToString(int terrain)
{
	if (terrain == 0) {
		return "plains";
	}
	else if (terrain == 1) {
		return "mountain";
	}
}

void Tile::drawItselfOnMap(sf::RenderWindow& window, sf::View& view)
{
	window.setView(view);
	window.draw(m_tileRec);
	if (hasFactory()) {
		window.draw(m_factorySprite);
	}
	window.draw(m_terrainSprite);
}

void Tile::drawItselfOnProduction(sf::RenderWindow & window, sf::View & view)
{
	window.setView(view);
	window.draw(m_tileRec);
	if (hasFactory()) {
		window.draw(m_factorySprite);
		window.draw(m_beingProduced);
	}
}

void Tile::drawItselfOnLogistics(sf::RenderWindow & window, sf::View & view)
{
	window.setView(view);
	sf::Text text;
	text.setFont(Renderer::font);
	text.setCharacterSize(15);
	text.setFillColor(sf::Color::Black);
	int i = 0;
	for (auto& equipment : m_storage) {
		m_equipmentBackground.setPosition(sf::Vector2f(10 , 10 + i * 35));
		text.setPosition(sf::Vector2f(12, 10 + i * 35 + 5));
		text.setString(equipment.first + " " + std::to_string(equipment.second));
		window.draw(m_equipmentBackground);
		window.draw(text);
		i++;
	}
	if (m_selectedEquipment != "None") {
		text.setPosition(200, 10);
		m_equipmentBackground.setPosition(sf::Vector2f(200, 10));
		text.setString(m_selectedEquipment);
		m_equipmentNumSelector.setValues(0, m_storage[m_selectedEquipment], m_equipmentNumSelected);
		window.draw(m_equipmentBackground);
		m_priorityGetter.drawItself(window, view);
		window.draw(text);
		m_equipmentNumSelector.drawItself(window, view);
	}
}


sf::Sprite & Tile::getBeingProduced()
{
	return m_beingProduced;
}

bool Tile::initializeTransportable()
{
	if (m_priorityGetter.getString() != "") {
		m_inLoadingBay = new TransportablePointer(m_selectedEquipment, m_equipmentNumSelected, std::stoi(m_priorityGetter.getString()), 1, m_playerNum);
		return true;
	}
	else {
		m_inLoadingBay = nullptr;
		return false;
	}
}

void Tile::launchTransportable()
{
	sender.push(*m_inLoadingBay);
	m_storage[m_selectedEquipment] -= m_equipmentNumSelected;
	m_equipmentNumSelector.setValues(0, m_storage[m_selectedEquipment], 0);
	delete m_inLoadingBay;
}
