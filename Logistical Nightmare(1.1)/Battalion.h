#pragma once
#include<string>
#include<SFML/Graphics.hpp>
#include<unordered_map>

enum class e_battalion_types { ARMOR, INFANTRY };

class Battalion {
public:
	static int total;
	static std::unordered_map<int, Battalion*> all_units;
	//static void deleteUnit(int ID);
public:
	//Battalion();
	//~Battalion();
private:
	const int FULL_MANPOWER = 1000;
	const float FULL_EXPERIENCE = 100;
	int m_ID;
	int m_manpower;
	e_battalion_types m_unitType;
	float m_experience;
	sf::Vector2i m_position;
};