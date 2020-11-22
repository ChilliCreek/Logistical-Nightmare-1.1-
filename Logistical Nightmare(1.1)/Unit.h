#pragma once
#include"pch.h"
#include<string>

class Unit 
{
private:
	std::string m_allegiance;
	float m_strength;
public:
	std::string getAllegience();
	bool isFriend(std::string&);
	float getStrength();
};