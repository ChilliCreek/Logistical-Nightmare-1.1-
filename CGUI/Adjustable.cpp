#include "pch.h"
#include "Adjustable.h"
#include"Functions.h"

Adjustable::Adjustable(uint ID, const std::string& label, float size, sf::Vector2f pos, float minVal, float maxVal, float defaultVal, const sf::Font& font)
{
	this->ID = ID;
	type = CGUI_TYPE::ADJUSTABLE;

	m_minValFloat = minVal;
	m_maxValFloat = maxVal;

	m_label.setFont(font);
	m_label.setPosition(pos);
	m_label.setString(label);
	m_label.setCharacterSize(30);
	m_label.setFillColor(sf::Color::White);
	m_size = size;

	m_spectrum.setSize(sf::Vector2f(size, 6.f));
	m_spectrum.setFillColor(sf::Color::Black);
	m_spectrum.setPosition(sf::Vector2f(m_label.getGlobalBounds().left + m_label.getLocalBounds().width + 10.f, pos.y + 15.f));

	m_minVal.setFont(font);
	m_minVal.setString(CGUI::floatToString(minVal, 2));
	m_minVal.setCharacterSize(10.f);
	m_minVal.setPosition(sf::Vector2f(m_spectrum.getPosition().x, m_spectrum.getPosition().y + 6.f));
	m_minVal.setFillColor(sf::Color::White);

	m_currentVal.setFont(font);
	m_currentVal.setString(CGUI::floatToString(defaultVal, 3));
	m_currentVal.setCharacterSize(10.f);
	m_currentVal.setPosition(m_spectrum.getPosition().x + defaultVal / (maxVal - minVal) * m_spectrum.getLocalBounds().width, m_spectrum.getPosition().y + 15.f);
	m_currentVal.setFillColor(sf::Color::White);

	m_maxVal.setFont(font);
	m_maxVal.setString(CGUI::floatToString(maxVal, 2));
	m_maxVal.setCharacterSize(10.f);
	m_maxVal.setPosition(sf::Vector2f(m_spectrum.getGlobalBounds().left + m_spectrum.getLocalBounds().width - m_maxVal.getLocalBounds().width, m_spectrum.getPosition().y + 6.f));
	m_maxVal.setFillColor(sf::Color::White);

	m_movable.setRadius(8.f);
	m_movable.setOrigin(m_movable.getRadius(), m_movable.getRadius());
	m_movable.setPosition(m_spectrum.getPosition().x + defaultVal / (maxVal - minVal) * m_spectrum.getLocalBounds().width, m_spectrum.getPosition().y + 3.f);
	m_movable.setOutlineThickness(-1.f);
	m_movable.setOutlineColor(sf::Color::Black);
	m_movable.setFillColor(sf::Color::White);
}

void Adjustable::drawItself(sf::RenderWindow& window, sf::View& view)
{
	window.setView(view);
	window.draw(m_label);
	window.draw(m_spectrum);
	window.draw(m_minVal);
	window.draw(m_currentVal);
	window.draw(m_maxVal);
	window.draw(m_movable);
}

void Adjustable::setMovablePosition(sf::Vector2f mousePos)
{
	if (mousePos.x < m_spectrum.getGlobalBounds().left) {
		m_movable.setPosition(m_spectrum.getGlobalBounds().left, m_movable.getPosition().y);
		m_currentVal.setPosition(m_spectrum.getGlobalBounds().left, m_currentVal.getPosition().y);
		m_currentVal.setString(CGUI::floatToString(getVal(), 3));
	}
	else if (mousePos.x > m_spectrum.getGlobalBounds().left + m_spectrum.getGlobalBounds().width) {
		m_movable.setPosition(m_spectrum.getGlobalBounds().left + m_spectrum.getGlobalBounds().width, m_movable.getPosition().y);
		m_currentVal.setPosition(m_spectrum.getGlobalBounds().left + m_spectrum.getGlobalBounds().width, m_currentVal.getPosition().y);
		m_currentVal.setString(CGUI::floatToString(getVal(), 3));
	}
	else {
		m_movable.setPosition(mousePos.x + mouseMovableOffset.x, m_movable.getPosition().y);
		m_currentVal.setPosition(mousePos.x + mouseMovableOffset.x, m_currentVal.getPosition().y);
		m_currentVal.setString(CGUI::floatToString(getVal(), 3));
	}
}

bool Adjustable::circleContains(sf::CircleShape& circle, sf::Vector2f point)
{
	if (distanceBetween2DPoints(circle.getPosition().x, circle.getPosition().y, point.x, point.y) < circle.getRadius()) {
		return true;
	}
	else {
		return false;
	}
}

float Adjustable::getVal() {
	return m_minValFloat + (m_movable.getPosition().x - m_spectrum.getPosition().x) / m_spectrum.getLocalBounds().width * (m_maxValFloat - m_minValFloat);
}

void Adjustable::setValues(float minVal, float maxVal, float defaultVal)
{
	m_minValFloat = minVal;
	m_maxValFloat = maxVal;
	m_minVal.setString(CGUI::floatToString(minVal, 2));
	m_maxVal.setString(CGUI::floatToString(maxVal, 2));
	m_currentVal.setString(CGUI::floatToString(defaultVal, 3));
	m_movable.setPosition(m_spectrum.getPosition().x + defaultVal / (maxVal - minVal) * m_spectrum.getLocalBounds().width, m_spectrum.getPosition().y + 3.f);
	m_currentVal.setPosition(m_spectrum.getPosition().x + defaultVal / (maxVal - minVal) * m_spectrum.getLocalBounds().width, m_spectrum.getPosition().y + 15.f);
}
