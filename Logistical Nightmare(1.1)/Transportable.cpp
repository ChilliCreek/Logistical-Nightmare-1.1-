#include "pch.h"
#include "Transportable.h"

Transportable::Transportable(const std::string & name, int quantity, int priority, sf::Vector2i destination, float transportTime) : m_name(name), m_quantity(quantity), m_priority(priority), m_destination(destination), m_transportTime(transportTime)
{

}

void Transportable::addPath(sf::Vector2i next)
{
	path.push_back(next);
	m_destination = next;
}

void Transportable::addPath(int nextX, int nextY)
{
	addPath(sf::Vector2i(nextX, nextY));
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
