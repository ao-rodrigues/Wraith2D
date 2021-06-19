#pragma once

#include <SDL_mixer.h>
#include "../ECS.h"
#include "../../AssetManager.h"

class Audio : public Component
{
public:
	enum AudioType
	{
		Music,
		SoundEffect,

		Count
	};

	Audio(AudioType type, const std::string& audioID)
		: _type(type)
		, _audioID(audioID)
	{ }

	void init() override
	{
		loadAudio(_type, _audioID);
	}

	/// <summary>
	/// Change the audio being played.
	/// </summary>
	/// <param name="type">The type of the new audio</param>
	/// <param name="audioID">The ID of the new audio</param>
	void setAudio(AudioType type, const std::string& audioID)
	{
		_type = type;
		_audioID = audioID;

		loadAudio(_type, _audioID);
	}

	/// <summary>
	/// Set whether this audio should loop or not.
	/// </summary>
	/// <param name="loop">If true, audio will loop, if false, it won't</param>
	inline void setLoop(bool loop)
	{
		_loop = loop;
	}

	/// <summary>
	/// Play the sound in this component.
	/// </summary>
	/// <param name="numLoops">The number of loops to play. Will be ignored if audio is set to loop.</param>
	/// <param name="channel">The channel where this audio will play. Only applies for audios of type SoundEffect.</param>
	void play(int numLoops = 0, int channel = -1)
	{
		switch (_type)
		{
		case Audio::Music:
			Mix_PlayMusic(_music, _loop ? -1 : numLoops);
			break;
		case Audio::SoundEffect:
			Mix_PlayChannel(channel, _soundEffect, numLoops);
			break;
		default:
			break;
		}
	}

	/// <summary>
	/// Pause the sound being played.
	/// </summary>
	/// <param name="channel">The channel of the audio to pause. Only applies for audios of type SoundEffect.</param>
	void pause(int channel = -1)
	{
		switch (_type)
		{
		case Audio::Music:
			Mix_PauseMusic();
			break;
		case Audio::SoundEffect:
			Mix_Pause(channel);
			break;
		default:
			break;
		}
	}

	/// <summary>
	/// Stop the sound being played.
	/// </summary>
	/// <param name="channel">The channel of the audio to stop. Only applies for audios of type SoundEffect.</param>
	void stop(int channel = -1)
	{
		switch (_type)
		{
		case Audio::Music:
			Mix_HaltMusic();
			break;
		case Audio::SoundEffect:
			Mix_HaltChannel(channel);
			break;
		default:
			break;
		}
	}

	/// <summary>
	/// Resume the sound that was paused.
	/// </summary>
	/// <param name="channel">The channel of the audio to resume. Only applies for audios of type SoundEffect.</param>
	void resume(int channel = -1)
	{
		switch (_type)
		{
		case Audio::Music:
			Mix_ResumeMusic();
			break;
		case Audio::SoundEffect:
			Mix_Resume(channel);
			break;
		default:
			break;
		}
	}

private:
	AudioType _type;
	std::string _audioID;
	bool _loop = false;
	Mix_Music* _music = nullptr;
	Mix_Chunk* _soundEffect = nullptr;

	void loadAudio(AudioType type, const std::string& audioID)
	{
		switch (type)
		{
		case Audio::Music:
			_music = AssetManager::instance().getMusic(audioID);
			break;
		case Audio::SoundEffect:
			_soundEffect = AssetManager::instance().getSoundEffect(audioID);
			break;
		default:
			break;
		}
	}
};