#include "pch.h"
#include "Writable.h"

Writable::Writable(sf::Vector2f size, sf::Vector2f pos, const sf::Font& font) : m_textField(size)
{
	m_string.setFont(font);
	m_string.setCharacterSize(size.y - 5);
	m_string.setFillColor(sf::Color::White);
	m_string.setPosition(pos);
	m_textField.setFillColor(sf::Color::Black);
	m_textField.setPosition(pos);
}

Writable::Writable(sf::Vector2f pos, const sf::Font& font) : Writable(sf::Vector2f(180, 30), pos, font)
{
}

void Writable::addCharacter(char input)
{
	if (input == 8) {
		m_string.setString(m_string.getString().substring(0, m_string.getString().getSize() - 1));
	}
	else if (input < 128) {
		m_string.setString(m_string.getString() + input);
	}
	if (m_string.getLocalBounds().width > m_textField.getLocalBounds().width) {
		m_string.setString(m_string.getString().substring(0, m_string.getString().getSize() - 1));
	}
}

void Writable::addNumber(char input)
{
	if (input == 8 || input == 46 || (input >= 48 && input <= 57)) {
		addCharacter(input);
	}
}

std::string Writable::getString()const
{
	return m_string.getString();
}

void Writable::drawItself(sf::RenderWindow & window, sf::View & view)
{
	window.setView(view);
	window.draw(m_label);
	window.draw(m_textField);
	window.draw(m_string);
}
