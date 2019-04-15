#pragma once

#ifdef LLF_AUDIO_FMOD

#ifndef AudioEngine_FMOD_HPP
#define AudioEngine_FMOD_HPP

#include "Lina/Audio/AudioEngine.hpp"

#include <string>
#include <map>
#include <fmod.hpp>

namespace LinaEngine
{
	class AudioEngine_FMOD : public AudioEngine
	{
	public:
		AudioEngine_FMOD();
		~AudioEngine_FMOD();

		void Initialize() override;
		void Start() override;
		void OnUpdate() override;
		void OnEvent(class Event& e) override;
		void OnInput(class InputEngine& i);


		
		void Update(float deltaTime);
		void LoadSFX(const std::string& path);
		void LoadSong(const std::string& path);
		void PlaySFX(const std::string& path, float minVolume, float maxVolume, float minPitch, float maxPitch);
		void PlaySong(const std::string& path);
		void StopSFXs();
		void StopSongs();
		void SetMasterVolume(float volume);
		void SetSFXsVolume(float volume);
		void SetSongsVolume(float volume);

	private:

		//Temporary. Write the these three functions to the Math later(or use the already implemented ones).
		float RandomBetween(float min, float max);
		// Octave is distance between two consecutive notes with the same name.
		float ChangeOctave(float frequency, float variation); 
		// Semitone is distance between any to adjacent notes.
		float ChangeSemitone(float frequency, float variation);

	private:

		typedef std::map<std::string, FMOD::Sound*> SoundMap;
		enum Category { CATEGORY_SFX, CATEGORY_SONG, CATEGORY_COUNT };
		void Load(Category type, const std::string& path);
		FMOD::System* m_System;
		FMOD::ChannelGroup* m_Master;
		FMOD::ChannelGroup* m_Groups[CATEGORY_COUNT];
		SoundMap m_Sounds[CATEGORY_COUNT];
		FMOD_MODE m_Modes[CATEGORY_COUNT];
		FMOD::Channel* m_CurrentSong;
		std::string m_CurrentSongPath;
		std::string m_NextSongPath;
		enum FadeState { FADE_NONE, FADE_IN, FADE_OUT };
		FadeState m_Fade;
	};
}

#endif

#endif
