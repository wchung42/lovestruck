#pragma once

#include "raylib.h"
#include "include/raylib-cpp.hpp"
#include "screen.hpp"
#include "animated_object.hpp"
#include "button.hpp"
#include <memory>

class TitleScreen : public Screen
{
private:
	raylib::Texture2DUnmanaged m_titleTexture;
	raylib::Vector2 m_titlePos {};
	AnimatedObject m_player;
	raylib::Vector2 m_playerPos {};
	raylib::Rectangle m_playerSourceRec {};
	raylib::Rectangle m_playerDestRec {};
	raylib::Font m_font;
	raylib::Texture2DUnmanaged m_playButtonTexture {};
	Button m_playButton;
	raylib::Texture2DUnmanaged m_creditsButtonTexture {};
	Button m_creditsButton;
	raylib::Texture2DUnmanaged m_quitButtonTexture {};
	Button m_quitButton;
public:
	TitleScreen(
		std::unordered_map<std::string,
		raylib::Texture2DUnmanaged> textures,
		raylib::Font& font
	);
	~TitleScreen();
	void InitScreen();
	void UpdateScreen(float deltaTime);
	void DrawScreen();
	void UnloadScreen();
};