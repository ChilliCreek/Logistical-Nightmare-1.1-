#pragma once
#include<iomanip>
#include<sstream>
#include"GUI_Drawable.h"

class Adjustable : public GUI_Drawable{
private:
	float m_size;
	bool m_clickedOrNot = false;
	sf::Vector2f mouseMovableOffset;
	static std::stringstream ss;
	sf::CircleShape m_movable;
	sf::Text m_minVal;
	float m_minValFloat;
	sf::Text m_currentVal;
	sf::Text m_maxVal;
	float m_maxValFloat;
	sf::RectangleShape m_spectrum;
public:
	Adjustable(sf::Vector2f pos, float minVal, float maxVal, float size, std::string labelString, float defaultVal);
	static std::string floatToString(float val, float precision);
	void drawItself(sf::RenderWindow& window, sf::View& view);
	void setMovablePosition(sf::Vector2f mousePos);
	bool isClicked();
	float getVal();
};