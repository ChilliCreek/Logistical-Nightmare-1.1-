#include "pch.h"
#include "Transportable.h"
#include"Functions.h"
constexpr auto PI = 3.141592;

Transportable::Transportable(const std::string & name, int quantity, int priority, float weight, int playerNum) : m_playerNum(playerNum), m_name(name), m_quantity(quantity), m_priority(priority), m_weight(weight)
{

}

void Transportable::addPath(sf::Vector2i origin, sf::Vector2i dest)
{
	quantities[origin] = m_quantity;
	if (absDiff(origin.x, dest.x) <= 1 && absDiff(origin.y, dest.y) <= 1) {
		quantities[dest] = 0;
		paths[origin] = dest;
	}
	else {
		sf::Vector2i offset = nextTileDirection(std::atan2f(origin.x - dest.x, dest.y - origin.y) * 180.f / PI);
		paths[origin] = origin + offset;
		addPathHelper(origin + offset, dest);
	}
}

void Transportable::addPathHelper(sf::Vector2i origin, sf::Vector2i dest)
{
	if (absDiff(origin.x, dest.x) <= 1 && absDiff(origin.y, dest.y) <= 1) {
		quantities[origin] = 0;
		quantities[dest] = 0;
		paths[origin] = dest;
	}
	else {
		sf::Vector2i offset = nextTileDirection(std::atan2f(origin.x - dest.x, dest.y - origin.y) * 180.f / PI);
		quantities[origin] = 0;
		paths[origin] = origin + offset;
		addPathHelper(origin + offset, dest);
	}
}

void Transportable::addPath(int originX, int originY, int destX, int destY)
{
	addPath(sf::Vector2i(originX, originY), sf::Vector2i(destX, destY));
}

bool Transportable::finished(sf::Vector2i tileNum)
{
	if (quantities[tileNum] > 0) {
		return false;
	}
	else {
		return true;
	}
}

int Transportable::update(int weightToMove, sf::Vector2i tileNum)
{
	int toReturn;
	if (weightToMove > (quantities[tileNum] * m_weight)) {
		toReturn = quantities[tileNum] * m_weight;
		quantities[tileNum] = 0;
		quantities[paths[tileNum]] += toReturn;
		return toReturn;
	}
	else {
		toReturn = static_cast<int>(weightToMove / m_weight);
		quantities[tileNum] -= toReturn;
		quantities[paths[tileNum]] += toReturn;
		return toReturn;
	}
}

int Transportable::updateNoNextTile(int weightToMove, sf::Vector2i tileNum)
{
	int toReturn;
	if (weightToMove > (quantities[tileNum] * m_weight)) {
		toReturn = quantities[tileNum] * m_weight;
		quantities[tileNum] = 0;
		return toReturn;
	}
	else {
		toReturn = static_cast<int>(weightToMove / m_weight);
		quantities[tileNum] -= toReturn;
		return toReturn;
	}
}

sf::Vector2i Transportable::getNextTile(sf::Vector2i current) {
	if (paths.find(current) == paths.end()) {
		throw std::invalid_argument("NO SUCH TILE FOUND IN PATHS");
	}
	return paths[current];
}

TransportablePointer::TransportablePointer(const std::string & name, int quantity, int priority, float weight, int playerNum)
{
	pt = std::make_shared<Transportable>(name, quantity, priority, weight, playerNum);
}

TransportablePointer::TransportablePointer(std::shared_ptr<Transportable> newPt)
{
	pt = newPt;
}

TransportablePointer::TransportablePointer()
{
	pt = nullptr;
}

