#pragma once
#include"CGUI.h"

class Writable : public CGUI_BASE{
public:
	/*
	  @param sf::Vector2i pos is the position of the top left corner of the Writable 
	  
	 */
	Writable(uint ID, const std::string label, sf::Vector2f size, sf::Vector2f pos, const sf::Font& font);
	void addCharacter(char input);
	void addNumber(char input);
	const std::string& getString()const;
	inline bool isClicked()const {
		return m_clickedOrNot;
	}
	inline bool setClicked(sf::Vector2f pos)
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
	std::string m_input;
	bool m_clickedOrNot = false;
	sf::Text m_label;
	sf::Vector2i position;
	float width;
	float height;
	sf::Text m_text;
	sf::RectangleShape m_textField;
};