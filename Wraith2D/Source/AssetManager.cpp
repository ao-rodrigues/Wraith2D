#include "AssetManager.h"
#include "Engine.h"
#include <iostream>

AssetManager::AssetManager()
{
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if ((IMG_Init(imgFlags) & imgFlags) != imgFlags)
	{
		std::cerr << "SDL image failed to initialize! Error: " << IMG_GetError() << std::endl;
	}

	if (TTF_Init() == -1)
	{
		std::cerr << "SDL ttf failed to initialize! Error: " << TTF_GetError() << std::endl;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr << "SDL mixer failed to initialize! Error: " << Mix_GetError() << std::endl;
	}
}

void AssetManager::clear()
{
	for (auto& texture : _textures)
	{
		SDL_DestroyTexture(texture.second);
	}
	_textures.clear();


	for (auto& font : _fonts)
	{
		TTF_CloseFont(font.second);
	}
	_fonts.clear();


	for (auto& music : _music)
	{
		Mix_FreeMusic(music.second);
	}
	_music.clear();


	for (auto& sfx : _soundEffects)
	{
		Mix_FreeChunk(sfx.second);
	}
	_soundEffects.clear();

	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	deleteInstance();
}

void AssetManager::loadTexture(const std::string& id, const std::string& path)
{
	if (!_textures.count(id))
	{
		SDL_Texture* texture = IMG_LoadTexture(Engine::instance().getRenderer(), path.c_str());
		if (texture)
		{
			_textures.emplace(id, texture);
			std::cout << "Texture: [" << path << "] loaded!" << std::endl;
		}
		else
		{
			std::cerr << "Failed to load texture! Error: " << IMG_GetError() << std::endl;
		}
	}
}

SDL_Texture* AssetManager::getTexture(const std::string& id)
{
	return _textures.count(id) ? _textures[id] : nullptr;
}

void AssetManager::loadFont(const std::string& id, const std::string& path, int fontSize)
{
	if (!_fonts.count(id))
	{
		TTF_Font* font = TTF_OpenFont(path.c_str(), fontSize);

		if (font)
		{
			_fonts.emplace(id, font);
			std::cout << "Font: [" << path << "] loaded!" << std::endl;
		}
		else
		{
			std::cerr << "Failed to load font! Error: " << TTF_GetError() << std::endl;
		}
	}
}

TTF_Font* AssetManager::getFont(const std::string& id)
{
	return _fonts.count(id) ? _fonts[id] : nullptr;
}

void AssetManager::loadMusic(const std::string& id, const std::string& path)
{
	if (!_music.count(id))
	{
		Mix_Music* music = Mix_LoadMUS(path.c_str());

		if (music)
		{
			_music.emplace(id, music);
			std::cout << "Music: [" << path << "] loaded!" << std::endl;
		}
		else
		{
			std::cerr << "Failed to load music! Error: " << Mix_GetError() << std::endl;
		}
	}
}

Mix_Music* AssetManager::getMusic(const std::string& id)
{
	return _music.count(id) ? _music[id] : nullptr;
}

void AssetManager::loadSoundEffect(const std::string& id, const std::string& path)
{
	if (!_soundEffects.count(id))
	{
		Mix_Chunk* sfx = Mix_LoadWAV(path.c_str());

		if (sfx)
		{
			_soundEffects.emplace(id, sfx);
			std::cout << "Sound effect: [" << path << "] loaded!" << std::endl;
		}
		else
		{
			std::cerr << "Failed to load sound effect! Error: " << Mix_GetError() << std::endl;
		}
	}
}

Mix_Chunk* AssetManager::getSoundEffect(const std::string& id)
{
	return _soundEffects.count(id) ? _soundEffects[id] : nullptr;
}

