#include "sound_manager.hpp"

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{

}

// Load a single sound file
void SoundManager::loadSound(const std::string& path)
{

	std::unique_ptr<raylib::Sound> sound = std::make_unique<raylib::Sound>(path);
	// Get name of file as key
	std::string baseFilename = path.substr(path.find_last_of("/\\") + 1);
	std::string::size_type const p(baseFilename.find_last_of('.'));
	std::string fileNameWithoutExtension = baseFilename.substr(0, p);
	m_sounds[fileNameWithoutExtension] = std::move(sound);
}

// Load multiple sound files
void SoundManager::loadSounds(const std::vector<std::string>& paths)
{
	for (auto& path : paths)
	{
		std::unique_ptr<raylib::Sound> sound = std::make_unique<raylib::Sound>(path);
		// Get name of file as key
		std::string baseFilename = path.substr(path.find_last_of("/\\") + 1);
		std::string::size_type const p(baseFilename.find_last_of('.'));
		std::string fileNameWithoutExtension = baseFilename.substr(0, p);
		m_sounds[fileNameWithoutExtension] = std::move(sound);
	}
}

// Play a single sound from RAM
void SoundManager::playSound(const std::string& name)
{
	if (m_sounds.find(name) != m_sounds.end())
	{
		m_sounds[name]->Play();
	}
}

// Load single music file
void SoundManager::loadMusic(const std::string& path)
{
	std::unique_ptr<raylib::Music> music = std::make_unique<raylib::Music>(path);
	// Get name of file as key
	std::string baseFilename = path.substr(path.find_last_of("/\\") + 1);
	std::string::size_type const p(baseFilename.find_last_of('.'));
	std::string fileNameWithoutExtension = baseFilename.substr(0, p);
	m_music[fileNameWithoutExtension] = std::move(music);
}

// Load multiple music files
void SoundManager::loadMusic(const std::vector<std::string>& paths)
{
	for (auto& path : paths)
	{
		std::unique_ptr<raylib::Music> music = std::make_unique<raylib::Music>(path);
		// Get name of file as key
		std::string baseFilename = path.substr(path.find_last_of("/\\") + 1);
		std::string::size_type const p(baseFilename.find_last_of('.'));
		std::string fileNameWithoutExtension = baseFilename.substr(0, p);
		m_music[fileNameWithoutExtension] = std::move(music);
	}
}

// Play single music track from RAM
void SoundManager::playMusic(const std::string& name)
{
	if (m_music.find(name) != m_music.end())
	{
		m_music[name]->Play();
	}
}

// Set music to looping
void SoundManager::setMusicLooping(const std::string& name)
{
	if (m_music.find(name) != m_music.end())
	{
		m_music[name]->SetLooping(true);
	}
}

// Update music
void SoundManager::updateMusic(const std::string& name)
{
	if (m_music.find(name) != m_music.end())
	{
		m_music[name]->Update();
	}
}