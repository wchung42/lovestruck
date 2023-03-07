#include "raylib.h"
#include "include/raylib-cpp.hpp"
#include "screen.hpp"
#include <iostream>

Screen::Screen() {}

Screen::Screen(std::unordered_map<std::string, raylib::Texture2DUnmanaged> textures) 
	: m_textures(textures)
{
}

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
	std::unordered_map<std::string, raylib::Texture2DUnmanaged>& textures)
{
	// Load textures into GPU
	for (auto& path : texturePaths)
	{
		raylib::Texture2DUnmanaged texture(path);
		// Get name of file as key
		std::string baseFilename = path.substr(path.find_last_of("/\\") + 1);
		std::string::size_type const p(baseFilename.find_last_of('.'));
		std::string fileWithoutExtension = baseFilename.substr(0, p);
		textures[fileWithoutExtension] = texture;
	}

	// Set textures to filter_bilinear flag for better scaling
	for (auto& [name, texture] : textures)
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