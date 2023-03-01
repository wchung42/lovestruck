#pragma once

#include "raylib.h"
#include "./include/raylib-cpp.hpp"
#include "screen.hpp"

class OptionsScreen : public Screen
{
public:
	void InitScreen();
	void UpdateScreen();
	void DrawScreen();
	void UnloadScreen();
};