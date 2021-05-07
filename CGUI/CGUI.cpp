#include"CGUI.h"
#include"Writable.h"
#include"Adjustable.h"

uint CGUI_MASTER::highestID = 0;

void CGUI::handleEvents(const sf::Event & event)
{
}

std::string CGUI_MASTER::floatToString(float val, float precision)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(precision) << val;
	return ss.str();
}

uint CGUI_MASTER::addWritable(const std::string label, sf::Vector2f size, sf::Vector2f pos, const sf::Font& font)
{
	m_all_items.push_back(new Writable(highestID, label, size, pos, font));
	highestID++;
	return highestID - 1;
}

uint CGUI_MASTER::addAdjustable(const std::string& label, float size, sf::Vector2f pos, float minVal, float maxVal, float defaultVal, const sf::Font& font)
{
    m_all_items.push_back(new Adjustable(highestID, label, size, pos, minVal, maxVal, defaultVal, font));
	highestID++;
	return highestID - 1;
}

void CGUI_MASTER::addItemToDraw(uint ID)
{
	m_drawOrder.push_back(ID);
}

void CGUI_MASTER::drawAll(sf::RenderWindow& window, sf::View& view)
{
	for (int i = 0; i < m_drawOrder.size(); i++) {
		m_all_items[m_drawOrder[i]]->drawItself(window, view);
	}
}

void CGUI_MASTER::clearitems()
{
	m_drawOrder.clear();
}
