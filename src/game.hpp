#pragma once

#include "include/raylib.h"
#include "include/raylib-cpp.hpp"
#include "screen.hpp"
#include "sound_manager.hpp"
#include <string>
#include <memory>
#include <unordered_map>

class Game
{
public:
	GameScreen m_currentScreen = LOGO;
private:
	// General game variables
	raylib::Window m_window {};
	int m_windowWidth {1280};
	int m_windowHeight {m_windowWidth / 16 * 9};
	int m_targetFPS {60};
	std::string m_title {"Lovestruck"};
	
	// Transition member variables
	float m_transAlpha {0.0f};
	bool m_onTransition {};
	bool m_transFadeOut {};
	int m_transFromScreen {-1};
	GameScreen m_transToScreen = UNKNOWN;
	GameScreen m_prevScreen = UNKNOWN;

	// Resource member variables
	std::unique_ptr<Screen> m_screen;					// Current screen
	raylib::AudioDevice m_audio;						// Audio device
	std::shared_ptr<SoundManager> m_soundManager;		// Sound manager
	std::unordered_map<std::string, raylib::Texture2DUnmanaged> m_textures;
	raylib::Font m_font;
	std::shared_ptr<int> m_score;
	bool m_exitGame {};
public:
	Game();
	~Game();
	// Initialize the game
	void Initialize();
	// Run the game loop
	void RunLoop();
	// Shutdown game properly
	void Shutdown();
private:
	// Helper functions for running the game loop
	void initializeTextures(
		const std::vector<std::string>& texturePaths,
		std::unordered_map<std::string, raylib::Texture2DUnmanaged>& textures
	);
	void UpdateGame(float deltaTime);
	void RenderGame();
	void ChangeToScreen(GameScreen screen);		// Change to screen, no transition effect
	void TransitionToScreen(GameScreen screen); // Request transition to next screen
	void UpdateTransition();					// Update transition effect
	void DrawTransition();						// Draw transition effect (fullscreen rectangle)
};