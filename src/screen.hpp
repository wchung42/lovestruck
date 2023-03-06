#pragma once

#include "raylib.h"
#include "include/raylib-cpp.hpp"
#include <string>
#include <unordered_map>

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef enum GameScreen { UNKNOWN = -1, LOGO = 0, TITLE, OPTIONS, GAMEPLAY, ENDING } GameScreen;

class Screen
{
protected:
	int m_framesCounter {};
	int m_finishScreen {};
	std::unordered_map<std::string, raylib::Texture2DUnmanaged> m_textures;
public:
	Screen();
	Screen(std::unordered_map<std::string, raylib::Texture2DUnmanaged> textures);
	~Screen();
	virtual void InitScreen();
	virtual void UpdateScreen(float deltaTime);
	virtual void DrawScreen();
	virtual void UnloadScreen();

	int GetFinishScreen() const { return m_finishScreen; } // Return the next screen
	void initializeTextures(
		const std::vector<std::string>& texturePaths,
		std::unordered_map<std::string, raylib::Texture2DUnmanaged>& textures
	);
	void initializeSounds(
		const std::vector<std::string>& soundPaths,
		std::vector<raylib::Sound>& sounds
	);

};