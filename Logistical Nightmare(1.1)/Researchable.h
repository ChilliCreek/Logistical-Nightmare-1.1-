#pragma once
#include"TextureHolder.h"
enum class e_researchStatus{RESEARCHED, IN_PROGRESS, NOT_RESEARCHED};

class Researchable
{
private:
	Sprite m_researchSprite;
	e_researchStatus m_researchStatus;
	string m_researchName;
	const float RESEARCH_TIME;
	Clock* m_researchClock;
public:
	Researchable(string, Vector2f, float);
	void doResearch(e_researchStatus);
	void update();
};
