#pragma once

#include "raylib.h"
#include "./include/raylib-cpp.hpp"
#include "screen.hpp"

class TitleScreen : public Screen
{
private:
	raylib::Text m_title;
	raylib::Vector2 m_titlePos {};
	raylib::Vector2 m_heartPos {};
	raylib::Rectangle m_heartSourceRec {};
	raylib::Rectangle m_heartDestRec {};
public:
	TitleScreen(std::unordered_map<std::string, raylib::Texture2DUnmanaged> textures);
	~TitleScreen();
	void InitScreen();
	void UpdateScreen(float deltaTime);
	void DrawScreen();
	void UnloadScreen();
};