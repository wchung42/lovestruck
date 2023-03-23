#include "texture_manager.hpp"

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
	for (auto& [name, texture] : m_textures)
	{
		texture.Unload();
	}
}

void TextureManager::loadTexture(const std::string& path)
{
	raylib::Texture2DUnmanaged texture(path);
	// Get name of file as key
	std::string baseFilename = path.substr(path.find_last_of("/\\") + 1);
	std::string::size_type const p(baseFilename.find_last_of('.'));
	std::string fileNameWithoutExtension = baseFilename.substr(0, p);
	m_textures[fileNameWithoutExtension] = texture;
	SetTextureFilter(m_textures[fileNameWithoutExtension], TEXTURE_FILTER_BILINEAR);
}

void TextureManager::loadTextures(const std::vector<std::string>& paths)
{
	// Load textures into GPU
	for (auto& path : paths)
	{
		raylib::Texture2DUnmanaged texture(path);
		// Get name of file as key
		std::string baseFilename = path.substr(path.find_last_of("/\\") + 1);
		std::string::size_type const p(baseFilename.find_last_of('.'));
		std::string fileNameWithoutExtension = baseFilename.substr(0, p);
		m_textures[fileNameWithoutExtension] = texture;
	}

	// Set textures to filter_bilinear flag for better scaling
	for (auto& [name, texture] : m_textures)
	{
		SetTextureFilter(texture, TEXTURE_FILTER_BILINEAR);
	}
}

void TextureManager::unloadTexture(const std::string& name)
{
	if (m_textures.find(name) != m_textures.end())
	{
		m_textures[name].Unload();
		m_textures.erase(name);
	}
}

void TextureManager::unloadTextures(const std::vector<std::string>& names)
{
	for (auto& name : names)
	{
		if (m_textures.find(name) != m_textures.end())
		{
			m_textures[name].Unload();
			m_textures.erase(name);
		}
	}
}

raylib::Texture2DUnmanaged TextureManager::getTexture(const std::string& name)
{
	if (m_textures.find(name) != m_textures.end())
	{
		return m_textures[name];
	}
	return {};
}