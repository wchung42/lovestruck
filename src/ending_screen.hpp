#pragma once

#include "raylib.h"
#include "./include/raylib-cpp.hpp"
#include "button.hpp"
#include "animated_object.hpp"
#include "screen.hpp"

class EndingScreen : public Screen
{
private:
	raylib::Texture2DUnmanaged m_playerTexture;
	AnimatedObject m_player;
	raylib::Texture2DUnmanaged m_restartButtonTexture;
	Button m_restartButton;
	raylib::Texture2DUnmanaged m_quitButtonTexture;
	Button m_quitButton;
	const raylib::Font m_font;
public:
	EndingScreen(
		std::unordered_map<std::string, raylib::Texture2DUnmanaged>& textures,
		const raylib::Font& font
	);
	~EndingScreen();
	void InitScreen();
	void UpdateScreen(float deltaTime);
	void DrawScreen();
	void UnloadScreen();
};