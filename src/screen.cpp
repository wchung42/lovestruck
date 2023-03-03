#include "raylib.h"
#include "include/raylib-cpp.hpp"
#include "screen.hpp"
#include <iostream>

Screen::Screen() {}

Screen::~Screen() {}

void Screen::InitScreen()
{
	// Initialize screen
}

void Screen::UpdateScreen(float deltaTime)
{
	// Update screen
}

void Screen::DrawScreen()
{
	// Draw screen
}

void Screen::UnloadScreen()
{
	// Unload screen variables
}

void Screen::initializeTextures(
	const std::vector<std::string>& texturePaths,
	std::vector<raylib::Texture2DUnmanaged>& textures)
{
	// Load textures into GPU
	for (auto& path : texturePaths)
	{
		raylib::Texture2DUnmanaged texture(path);
		textures.push_back(texture);
	}

	// Set textures to filter_bilinear flag for better scaling
	for (auto& texture : textures)
	{
		SetTextureFilter(texture, TEXTURE_FILTER_BILINEAR);
	}
}

void Screen::initializeSounds(
	const std::vector<std::string>& soundPaths,
	std::vector<raylib::Sound>& sounds)
{
	for (auto& path : soundPaths)
	{
		//raylib::Sound sound(path);
		sounds.push_back(raylib::Sound::Sound(path));
	}
}