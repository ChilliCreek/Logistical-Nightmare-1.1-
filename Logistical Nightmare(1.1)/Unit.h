#pragma once
#include"pch.h"
#include<string>

class Unit 
{
public:
	float getStrength();
private:
	float m_strength;
	float m_armor;
	float m_antiPersonnel;
};