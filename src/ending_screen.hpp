#pragma once

#include "raylib.h"
#include "./include/raylib-cpp.hpp"
#include "screen.hpp"

class EndingScreen : public Screen
{
public:
	EndingScreen(std::unordered_map<std::string, raylib::Texture2DUnmanaged> textures);
	~EndingScreen();
	void InitScreen();
	void UpdateScreen(float deltaTime);
	void DrawScreen();
	void UnloadScreen();
};