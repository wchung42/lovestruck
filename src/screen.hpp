#pragma once

#include "include/raylib.h"
#include "include/raylib-cpp.hpp"
#include "player.hpp"
#include "arrow.hpp"
#include "target.hpp"
#include "target_spawner.hpp"
#include "cloud.hpp"
#include "button.hpp"
#include "animated_object.hpp"
#include <string>
#include <unordered_map>

//----------------------------------------------------------------------------------
// Base screen class declaration
//----------------------------------------------------------------------------------
typedef enum GameScreen { UNKNOWN = -1, LOGO = 0, TITLE, OPTIONS, GAMEPLAY, ENDING, CREDITS, EXIT} GameScreen;

class Screen
{
protected:
	int m_framesCounter {};
	int m_nextScreen {};
	std::unordered_map<std::string, raylib::Texture2DUnmanaged> m_textures;
public:
	Screen();
	Screen(std::unordered_map<std::string, raylib::Texture2DUnmanaged> textures);
	virtual ~Screen();
	virtual void UpdateScreen(float deltaTime);
	virtual void DrawScreen();
	int getNextScreen() { return m_nextScreen; }
};


//----------------------------------------------------------------------------------
// Logo screen class declaration
//----------------------------------------------------------------------------------
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
	LogoScreen();
	~LogoScreen();
	void UpdateScreen(float deltaTime);
	void DrawScreen();
};


//----------------------------------------------------------------------------------
// Options screen class declaration
//----------------------------------------------------------------------------------
class OptionsScreen : public Screen
{
public:
	OptionsScreen();
	~OptionsScreen();
	void UpdateScreen();
	void DrawScreen();
};


//----------------------------------------------------------------------------------
// Title screen class declaration
//----------------------------------------------------------------------------------
class TitleScreen : public Screen
{
private:
	raylib::Texture2DUnmanaged m_titleTexture;
	raylib::Vector2 m_titlePos {};
	AnimatedObject m_player;
	raylib::Font m_font;
	raylib::Texture2DUnmanaged m_playButtonTexture {};
	Button m_playButton;
	raylib::Texture2DUnmanaged m_creditsButtonTexture {};
	Button m_creditsButton;
	raylib::Texture2DUnmanaged m_quitButtonTexture {};
	Button m_quitButton;
public:
	TitleScreen(
		std::unordered_map<std::string, raylib::Texture2DUnmanaged>& textures
	);
	~TitleScreen();
	void UpdateScreen(float deltaTime);
	void DrawScreen();
};


//----------------------------------------------------------------------------------
// Gameplay screen class declaration
//----------------------------------------------------------------------------------
class GameplayScreen : public Screen
{
private:
	std::unique_ptr<Player> m_player;
	std::unique_ptr<std::vector<std::shared_ptr<Arrow>>> m_arrows;
	std::unique_ptr<std::vector<std::unique_ptr<Target>>> m_targets;
	std::unique_ptr<TargetSpawner> m_spawner;
	std::vector<Cloud> m_clouds;
	std::vector<raylib::Sound> m_sounds;
	std::shared_ptr<int> m_score;
	bool m_gameOver {};
	const raylib::Font& m_font;
public:
	GameplayScreen(
		std::unordered_map<std::string, raylib::Texture2DUnmanaged>& textures,
		const raylib::Font& font,
		std::shared_ptr<int> score
	);
	~GameplayScreen();
	void UpdateScreen(float deltaTime);
	void DrawScreen();
	int getScore() { return *m_score; }
};


//----------------------------------------------------------------------------------
// Credits screen class declaration
//----------------------------------------------------------------------------------
class CreditsScreen : public Screen
{
private:
	raylib::Font& m_font;
	raylib::Texture2DUnmanaged m_backButtonTexture;
	Button m_backButton;
	GameScreen m_prevScreen;

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
		raylib::Texture2DUnmanaged backButtonTexture,
		GameScreen prevScreen
	);
	~CreditsScreen();
	void UpdateScreen(float deltaTime);
	void DrawScreen();
};


//----------------------------------------------------------------------------------
// Ending screen class declaration
//----------------------------------------------------------------------------------
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
	void UpdateScreen(float deltaTime);
	void DrawScreen();
};