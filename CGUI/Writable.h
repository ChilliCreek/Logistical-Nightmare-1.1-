#pragma once
#include"GUI_Drawable.h"

class Writable : public GUI_Drawable{
public:
	Writable(sf::Vector2f size, sf::Vector2f pos, const sf::Font& font);
	Writable(sf::Vector2f pos, const sf::Font& font);
	void addCharacter(char input);
	void addNumber(char input);
	std::string getString()const;
	inline bool isClicked()const {
		return m_clickedOrNot;
	}
	inline bool setClickedTrue(sf::Vector2f pos)
	{
		if (m_textField.getGlobalBounds().contains(pos)) {
			m_clickedOrNot = true;
			return true;
		}
		return false;
	}
	inline void setClickedFalse() {
		m_clickedOrNot = false;
	}
	void drawItself(sf::RenderWindow& window, sf::View& view);
private:
	sf::Text m_string;
	sf::RectangleShape m_textField;
};