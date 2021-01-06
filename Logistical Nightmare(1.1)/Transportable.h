#pragma once
#include<SFML/Graphics.hpp>
#include<deque>

class Transportable {
public:
	Transportable(const std::string& name, int quantity, int priority, float transportTime, int playerNum);
	void addPath(sf::Vector2i next);
	void addPath(int nextX, int nextY);
	bool finished();
	/*!
	Given how much time has elapsed in a float, returns how many "name" were transported in an integer.
	*/
	int update(float time);

	inline const std::deque<sf::Vector2i>& getPath() {
		return path;
	}
	inline int getPriority()const {
		return m_priority;
	}
private:
	int m_playerNum;
	float m_timeTracker = 0;
	float m_transportTime;
	int m_priority;
	sf::Vector2i m_destination;
	std::string m_name;
	int m_quantity;
	std::deque <sf::Vector2i> path;
};

struct TransportablePointer{
public:
	TransportablePointer(const std::string& name, int quantity, int priority, float transportTime, int playerNum);
	TransportablePointer();
	std::shared_ptr<Transportable> pt;
};

struct TransportablePointerCompare {
	bool operator()(const TransportablePointer& first, const TransportablePointer& second) {
		return first.pt->getPriority() < second.pt->getPriority();
	}
};