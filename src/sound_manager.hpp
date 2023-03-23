#pragma once

#include "include/raylib.h"
#include "include/raylib-cpp.hpp"
#include <unordered_map>
#include <memory>

class SoundManager
{
private:
	std::unordered_map<std::string, std::unique_ptr<raylib::Sound>> m_sounds;
	std::unordered_map<std::string, std::unique_ptr<raylib::Music>> m_music;
public:
	SoundManager();
	~SoundManager();
	void loadSound(const std::string& path);
	void loadSounds(const std::vector<std::string>& paths);
	void playSound(const std::string& name);
	void loadMusic(const std::string& path);
	void loadMusic(const std::vector<std::string>& paths);
	void playMusic(const std::string& name);
	void setMusicLooping(const std::string& name);
	void updateMusic(const std::string& name);
};