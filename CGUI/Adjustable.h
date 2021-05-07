#pragma once
#include"CGUI.h"

class Adjustable : public CGUI_BASE{
public:
	Adjustable(uint ID, const std::string& label, float size, sf::Vector2f pos, float minVal, float maxVal, float defaultVal, const sf::Font& font);
	void drawItself(sf::RenderWindow& window, sf::View& view);
	void setMovablePosition(sf::Vector2f mousePos);
	inline bool isClicked()const {
		return m_clickedOrNot;
	}
	inline void setClickedOrNot(bool clickedOrNot, sf::Vector2f mouseGlobalPosition) {
		if (clickedOrNot) {
			mouseMovableOffset = sf::Vector2f(m_movable.getPosition().x - mouseGlobalPosition.x, m_movable.getPosition().y - mouseGlobalPosition.y);
		}
		m_clickedOrNot = clickedOrNot;
	}
	static bool circleContains(sf::CircleShape& circle, sf::Vector2f point);
	inline bool movableContains(sf::Vector2f point) {
		return circleContains(m_movable, point);
	}
	float getVal();
	void setValues(float minVal, float maxVal, float defaultVal);
private:
	bool m_clickedOrNot = false;
	sf::Text m_label;
	float m_size;
	bool m_clickedOrNot = false;
	sf::Vector2f mouseMovableOffset;
	sf::CircleShape m_movable;
	sf::Text m_minVal;
	float m_minValFloat;
	sf::Text m_currentVal;
	sf::Text m_maxVal;
	float m_maxValFloat;
	sf::RectangleShape m_spectrum;
};