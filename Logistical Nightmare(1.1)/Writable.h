#pragma once
#include"GUI_Drawable.h"

class Writable : public GUI_Drawable{
private:
	sf::Text m_label;
	sf::RectangleShape m_textField;
public:
	//void addCharacter();
	//std::string getString();
	//bool isClicked();
};