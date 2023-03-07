#pragma once

#include "raylib.h"
#include "./include/raylib-cpp.hpp"
#include "button.hpp"
#include "animated_object.hpp"
#include "screen.hpp"

class EndingScreen : public Screen
{
private:
	AnimatedObject m_player;
	Button m_playAgainButton;
	Button m_creditsButton;
	Button m_quitButton;
	const raylib::Font& m_font;
	std::shared_ptr<int> m_score;
	raylib::Vector2 m_textPos {};
public:
	EndingScreen(
		std::unordered_map<std::string, raylib::Texture2DUnmanaged>& textures,
		const raylib::Font& font,
		const std::shared_ptr<int> m_score
	);
	~EndingScreen();
	void InitScreen();
	void UpdateScreen(float deltaTime);
	void DrawScreen();
	void UnloadScreen();
};