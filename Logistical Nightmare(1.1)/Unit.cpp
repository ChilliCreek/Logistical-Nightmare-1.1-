#pragma once
#include"pch.h"
#include"Unit.h"

std::string Unit::getAllegience()
{
	return m_allegiance;
}
bool Unit::isFriend(std::string& const alligiance)
{
	return alligiance == m_allegiance;
}
float Unit::getStrength()
{
	return m_strength;
}

