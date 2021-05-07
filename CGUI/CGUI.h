#pragma once
#include"SFML/Graphics.hpp"
#include<iomanip>
#include<sstream>

#define uint unsigned int

enum class CGUI_TYPE{WRITABLE, ADJUSTABLE, DRAWABLE};

class CGUI_BASE {
public:
	uint ID;
	CGUI_TYPE type;
	virtual void drawItself(sf::RenderWindow& window, sf::View& view) = 0;
};

class CGUI_MASTER{
public:
	static sf::RenderWindow& window;
	static uint highestID;
	static std::vector<CGUI_BASE*> m_all_items;
	static void handleEvents(const sf::Event& event);
	static std::string floatToString(float val, float precision);
	static uint addWritable(const std::string label, sf::Vector2f size, sf::Vector2f pos, const sf::Font& font);
	static uint addAdjustable(const std::string& label, float size, sf::Vector2f pos, float minVal, float maxVal, float defaultVal, const sf::Font& font);
private:
	std::vector<uint> m_drawOrder;
	void addItemToDraw(uint ID);
	void drawAll(sf::RenderWindow& window, sf::View& view);
	void clearitems();
};

class Drawable {

};
