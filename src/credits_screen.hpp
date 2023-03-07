#pragma once

#include "raylib.h"
#include "include/raylib-cpp.hpp"
#include "button.hpp"
#include "animated_object.hpp"
#include "screen.hpp"

class CreditsScreen : public Screen
{
private:
	raylib::Font& m_font;
	raylib::Texture2DUnmanaged m_backButtonTexture;
	Button m_backButton;

	// Headings
	raylib::Vector2 m_designerHeadingPos;
	raylib::Text m_designerHeading;
	raylib::Vector2 m_fontsHeadingPos;
	raylib::Text m_fontsHeading;
	raylib::Vector2 m_sfxHeadingPos;
	raylib::Text m_sfxHeading;

	// Text
	raylib::Vector2 m_designerTextPos;
	raylib::Text m_designerText;
	raylib::Vector2 m_fontsTextPos;
	raylib::Text m_fontsText;
	raylib::Vector2 m_sfxTextPos;
	raylib::Text m_sfxText;
public:
	CreditsScreen(
		raylib::Font& font,
		raylib::Texture2DUnmanaged backButtonTexture
	);
	~CreditsScreen();
	void InitScreen();
	void UpdateScreen(float deltaTime);
	void DrawScreen();
	void UnloadScreen();
};