#pragma once
#include<SFML/Graphics.hpp>
#include<Functions.h>
#include<deque>

class Transportable {
public:
	Transportable(const std::string& name, int quantity, int priority, float weight, int playerNum);
	void addPath(sf::Vector2i origin, sf::Vector2i dest);
	void addPath(int originX, int originY, int destX, int destY);
	bool finished(sf::Vector2i tileNum);
	/*!
	Given how much time has elapsed in an integer, returns how many "name" were transported in an integer.
	*/
	int update(int weightToMove, sf::Vector2i tileNum);
	int updateNoNextTile(int weightToMove, sf::Vector2i tileNum);
	inline int getPriority()const {
		return m_priority;
	}
	inline const std::string& getName() {
		return m_name;
	}
	sf::Vector2i getNextTile(sf::Vector2i current);
	inline int getQuantity(sf::Vector2i tileNum) {
		return quantities[tileNum];
	}
	inline std::map<sf::Vector2i, sf::Vector2i, SFVector2iComp >& getPaths() {
		return paths;
	}
private:
	void addPathHelper(sf::Vector2i origin, sf::Vector2i dest);
	int m_playerNum;
	float m_weight;
	int m_priority;
	sf::Vector2i m_destination;
	std::string m_name;
	int m_quantity;
	std::map<sf::Vector2i, sf::Vector2i, SFVector2iComp > paths;
	std::map<sf::Vector2i, int, SFVector2iComp > quantities;
};

struct TransportablePointer{
public:
	TransportablePointer(const std::string& name, int quantity, int priority, float transportTime, int playerNum);
	TransportablePointer(std::shared_ptr<Transportable> newPt);
	TransportablePointer();
	std::shared_ptr<Transportable> pt;
};

struct TransportablePointerCompare {
	bool operator()(const TransportablePointer& first, const TransportablePointer& second) {
		return first.pt->getPriority() < second.pt->getPriority();
	}
};