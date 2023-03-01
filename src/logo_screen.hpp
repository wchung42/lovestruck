#pragma once

#include "raylib.h"
#include "include/raylib-cpp.hpp"
#include "screen.hpp"

class LogoScreen : public Screen
{
private:
	int m_logoPositionX {};
	int m_logoPositionY {};
	int m_lettersCount {};
	int m_topSideRecWidth {};
	int m_leftSideRecHeight {};
	int m_bottomSideRecWidth {};
	int m_rightSideRecHeight {};
	int m_state {};				// Logo animation states
	float m_alpha {1.0f};         // Useful for fading
public:
	void InitScreen();
	void UpdateScreen(float deltaTime);
	void DrawScreen();
	void UnloadScreen();
};