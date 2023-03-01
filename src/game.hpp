#pragma once

#include "raylib.h"
#include "include/raylib-cpp.hpp"
#include "screen.hpp"
#include <string>
#include <memory>

class Game
{
public:
	GameScreen m_currentScreen = LOGO;
private:
	raylib::Window m_window {};
	int m_windowWidth {1280};
	int m_windowHeight {m_windowWidth / 16 * 9};
	int m_targetFPS {60};
	std::string m_title {"raylib-game-template"};
	float m_transAlpha {0.0f};
	bool m_onTransition {};
	bool m_transFadeOut {};
	int m_transFromScreen {-1};
	std::unique_ptr<Screen> m_screen;
	GameScreen m_transToScreen = UNKNOWN;
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
	void UpdateGame(float deltaTime);
	void RenderGame();
	void ChangeToScreen(GameScreen screen);		// Change to screen, no transition effect
	void TransitionToScreen(GameScreen screen); // Request transition to next screen
	void UpdateTransition();					// Update transition effect
	void DrawTransition();						// Draw transition effect (fullscreen rectangle)
};