#include "pch.h"
#include "Writable.h"

Writable::Writable(uint ID, const std::string label, sf::Vector2f size, sf::Vector2f pos, const sf::Font& font) : m_textField(size), position(pos)
{
	this->ID = ID;
	type = CGUI_TYPE::WRITABLE;

	m_label.setFont(font);
	m_label.setString(label);
	m_label.setPosition(pos);
	m_label.setCharacterSize(size.y - 5);
	m_label.setFillColor(sf::Color::Black);

	m_text.setFont(font);
	m_text.setCharacterSize(size.y - 5);
	m_text.setFillColor(sf::Color::White);
	m_text.setPosition(sf::Vector2f(pos.x + m_label.getLocalBounds().width, pos.y + m_label.getLocalBounds().height));

	m_textField.setFillColor(sf::Color::Black);
	m_textField.setPosition(m_text.getPosition());

	width = m_label.getLocalBounds().width + m_textField.getLocalBounds().width;
	width = size.y;
}

void Writable::addCharacter(char input)
{
	if (input == 8) {
		m_input = m_input.substr(0, m_input.length() - 1);
		m_text.setString(m_input);
	}
	else if (input < 128) {
		m_input += input;
		m_text.setString(m_input);
	}
	if (m_text.getLocalBounds().width > m_textField.getLocalBounds().width) {
		m_text.setString(m_input.substr(0, m_input.length() - 1));
	}
}

void Writable::addNumber(char input)
{
	if (input == 8 || input == 46 || (input >= 48 && input <= 57)) {
		addCharacter(input);
	}
}

const std::string& Writable::getString()const
{
	return m_input;;
}

void Writable::drawItself(sf::RenderWindow & window, sf::View & view)
{
	window.setView(view);
	window.draw(m_label);
	window.draw(m_textField);
	window.draw(m_text);
}
