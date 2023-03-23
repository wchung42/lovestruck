#pragma once

#include "include/raylib.h"
#include "include/raylib-cpp.hpp"
#include <string>
#include <unordered_map>

class TextureManager
{
private:
	std::unordered_map<std::string, raylib::Texture2DUnmanaged> m_textures;
public:
	TextureManager();
	~TextureManager();
	void loadTexture(const std::string& path);
	void loadTextures(const std::vector<std::string>& paths);
	void unloadTexture(const std::string& name);
	void unloadTextures(const std::vector<std::string>& names);
	raylib::Texture2DUnmanaged getTexture(const std::string& name);
	//void setTexture(const std::string& oldTextureName, const std::string& pathToNewTexture);
};