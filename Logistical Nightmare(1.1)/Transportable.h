#pragma once
#include<SFML/Graphics.hpp>
#include<deque>

class Transportable {
public:
	inline int getPriority()const {
		return m_priority;
	}
	Transportable(const std::string& name, int quantity, int priority, sf::Vector2i destination, float transportTime);
	void addPath(sf::Vector2i next);
	void addPath(int nextX, int nextY);
	bool finished();
	/*!
	Given how much time has elapsed in a float, returns how many "name" were transported in an integer.
	*/
	int update(float time);
private:
	float m_timeTracker = 0;
	float m_transportTime;
	int m_priority;
	sf::Vector2i m_destination;
	std::string m_name;
	int m_quantity;
	std::deque <sf::Vector2i> path;
};
struct Compare {
	bool operator() (const Transportable& first, const Transportable& second){
		return first.getPriority() < second.getPriority();
	}
};