#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <unordered_map>
#include <string>

#include "Singleton.h"

class AssetManager : public Singleton<AssetManager>
{
public:
	AssetManager();
	~AssetManager() = default;

	/// <summary>
	/// Clears all loaded assets.
	/// </summary>
	void clear();

	/// <summary>
	/// Loads a new texture asset.
	/// </summary>
	/// <param name="id">The ID that will be used to identify this new texture</param>
	/// <param name="path">The path to the texture asset</param>
	void loadTexture(const std::string& id, const std::string& path);

	/// <summary>
	/// Returns a previously loaded texture identified by id.
	/// </summary>
	/// <param name="id">The texture ID</param>
	/// <returns>A pointer to the texture, or nullptr if it doesn't exist</returns>
	SDL_Texture* getTexture(const std::string& id);

	/// <summary>
	/// Loads a new font asset.
	/// </summary>
	/// <param name="id">The ID that will be used to identify this new font</param>
	/// <param name="path">The path to the font asset</param>
	/// <param name="fontSize">The font size</param>
	void loadFont(const std::string& id, const std::string& path, int fontSize);

	/// <summary>
	/// Returns a previously loaded font asset.
	/// </summary>
	/// <param name="id">The font ID</param>
	/// <returns>A pointer to the font, or nullptr if it doesn't exist</returns>
	TTF_Font* getFont(const std::string& id);

	/// <summary>
	/// Loads a new music asset.
	/// </summary>
	/// <param name="id">The ID that will be used to identify this new music</param>
	/// <param name="path">The path to the music asset</param>
	void loadMusic(const std::string& id, const std::string& path);

	/// <summary>
	/// Returns a previously loaded music asset.
	/// </summary>
	/// <param name="id">The music asset ID</param>
	/// <returns>A pointer to the music asset, or nullptr if it doesn't exst</returns>
	Mix_Music* getMusic(const std::string& id);

	/// <summary>
	/// Loads a new sound effect asset.
	/// </summary>
	/// <param name="id">The ID that will be used to identify this new sound effect</param>
	/// <param name="path">The path to the sound effect asset</param>
	void loadSoundEffect(const std::string& id, const std::string& path);

	/// <summary>
	/// Returns a previously loaded sound effect asset.
	/// </summary>
	/// <param name="id">The sound effect asset ID</param>
	/// <returns>A pointer to the sound effect asset, or nullptr iif it doesn't exist</returns>
	Mix_Chunk* getSoundEffect(const std::string& id);

private:
	std::unordered_map<std::string, SDL_Texture*> _textures;
	std::unordered_map<std::string, TTF_Font*> _fonts;
	std::unordered_map<std::string, Mix_Music*> _music;
	std::unordered_map<std::string, Mix_Chunk*> _soundEffects;
};