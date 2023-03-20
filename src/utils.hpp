#pragma once

#include "include/raylib.h"
#include "include/raylib-cpp.hpp"
#include <unordered_map>

namespace utils 
{
	void initializeTextures(
		const std::vector<std::string>& texturePaths,
		std::unordered_map<std::string, raylib::Texture2DUnmanaged>& textures);

	void initializeSounds(
		const std::vector<std::string>& soundPaths,
		std::vector<raylib::Sound>& sounds
	);
}