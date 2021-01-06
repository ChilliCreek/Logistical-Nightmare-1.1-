#include "pch.h"
#include "Transportable.h"
#include"Functions.h"
constexpr auto PI = 3.141592;

Transportable::Transportable(const std::string & name, int quantity, int priority, float transportTime, int playerNum) : m_playerNum(playerNum), m_name(name), m_quantity(quantity), m_priority(priority), m_transportTime(transportTime)
{

}

void Transportable::addPath(sf::Vector2i next)
{
	addPath(next.x, next.y);
}

void Transportable::addPath(int nextX, int nextY)
{
	int currX = path.back().x;
	int currY = path.back().y;
	if (absDiff(currX, nextX) <= 1 && absDiff(currY, nextY) <= 1) {
		path.push_back(sf::Vector2i(nextX, nextY));
	}
	else {
		sf::Vector2i offset = nextTileDirection(std::atan2f(currX - nextX, nextY - currY) * 180.f / PI);
		path.push_back(sf::Vector2i(currX + offset.x, currY + offset.y));
		addPath(nextX, nextY);
	}
}

bool Transportable::finished()
{
	if (m_quantity <= 0) {
		return true;
	}
	else {
		return false;
	}
}

int Transportable::update(float time)
{
	m_timeTracker += time;
	if (m_timeTracker > m_transportTime) {
		int moved = static_cast<int>(m_timeTracker / m_transportTime);
		m_quantity -= moved;
		m_timeTracker -= moved * m_transportTime;
		return moved;
	}
	return 0;
}

TransportablePointer::TransportablePointer(const std::string & name, int quantity, int priority, float transportTime, int playerNum)
{
	pt = std::make_shared<Transportable>(name, quantity, priority, transportTime, playerNum);
}

TransportablePointer::TransportablePointer()
{
	pt = nullptr;
}

