#pragma once
#include"pch.h"
#include"Engine.h"

int main() {
	Renderer::font.loadFromFile("font/Stanberry.ttf");
	Engine engine;
	engine.run();
	return 0;
}
