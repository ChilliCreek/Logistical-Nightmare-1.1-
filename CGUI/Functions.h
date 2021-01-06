#pragma once
#include<string>

template<typename T>
inline T abs(T inp) {
	return (inp > 0) ? inp : (-inp);
}

template<typename T>
inline T absDiff(T first, T second) {
	return abs(first - second);
}

template<typename F, typename S>
inline bool equals(F first, S second) {
	if (abs(first - second) < 0.0001)return true;
	else return false;
}

inline float distanceBetween2DPoints(float x1, float y1, float x2, float y2) {
	return std::sqrt(std::powf(x1 - x2, 2) + std::powf(y1 - y2, 2));
}
/*!
Takes in an angle in degrees, and returns which of the eight adjacent tiles
 the angle is pointing at. x is row and y is column and the origin is at the top left.
*/
inline sf::Vector2i nextTileDirection(float angle) {
	if (angle > 180.f || angle < -180.f) {
		throw std::invalid_argument("angle out of range");
	}
	if (equals(angle, 45.f)) {
		return sf::Vector2i(-1, 1);
	}
	else if (equals(angle, 135.f)) {
		return sf::Vector2i(-1, -1);
	}
	else if (equals(angle, -45.f)) {
		return sf::Vector2i(1, 1);
	}
	else if (equals(angle, -135.f)) {
		return sf::Vector2i(1, -1);
	}
	else if (angle > 45.f && angle < 135.f) {
		return sf::Vector2i(-1, 0);
	}
	else if (angle > -45.f && angle < 45.f) {
		return sf::Vector2i(0, 1);
	}
	else if (angle > -135.f && angle < -45.f) {
		return sf::Vector2i(1, 0);
	}
	else if (angle < 180.0001f || angle > -180.0001f) {
		return sf::Vector2i(0, -1);
	}
}