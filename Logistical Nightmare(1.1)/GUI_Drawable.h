#pragma once
#include"SFML/Graphics.hpp"
#include<string>

class GUI_Drawable {
protected:
	bool m_clickedOrNot = false;
	sf::Text m_label;
public:
	virtual void drawItself(sf::RenderWindow& window, sf::View& view) = 0;
	virtual bool isClicked()const = 0;
};