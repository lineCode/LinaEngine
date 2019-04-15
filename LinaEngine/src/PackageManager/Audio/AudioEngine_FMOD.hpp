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

		/* Temporary OnInpu method for testing the sound effects and songs.  */
		void OnInput(class InputEngine& i);


		/* Update method for the FMOD system.  */
		void Update(float deltaTime);

		/* Load Sound Effects from the given path and insert into the SoundMap.  */
		void LoadSFX(const std::string& path);

		/* Load Songs from the given path and insert into the SoundMap.  */
		void LoadSong(const std::string& path);

		/* Play the Sound Effect that loaded. Additional parameters are for deciding to the volume and pitch interval.  */
		void PlaySFX(const std::string& path, float minVolume, float maxVolume, float minPitch, float maxPitch);

		/* Play the Song that loaded.  */
		void PlaySong(const std::string& path);

		/* Stop all of the Sound Effects that are active at the time.  */
		void StopSFXs();

		/* Stop all of the Songs that are active at the time.  (Actually there will always be 1 song active)  */
		void StopSongs();

		/* Set the master volume which will affect both Sound Effects and Songs.  */
		void SetMasterVolume(float volume);

		/* Set the Sound Effects volume.  */
		void SetSFXsVolume(float volume);

		/* Set the Song volume.  */
		void SetSongsVolume(float volume);

	public:
		enum Category { CATEGORY_SFX, CATEGORY_SONG, CATEGORY_COUNT };

		enum FadeState { FADE_NONE, FADE_IN, FADE_OUT };

	private:

		void Load(Category type, const std::string& path);

		//Temporary. Write the these three functions to the Math later(or use the already implemented ones).
		float RandomBetween(float min, float max);
		// Octave is distance between two consecutive notes with the same name.
		float ChangeOctave(float frequency, float variation); 
		// Semitone is distance between any to adjacent notes.
		float ChangeSemitone(float frequency, float variation);

	private:

		typedef std::map<std::string, FMOD::Sound*> SoundMap;
		FMOD::System* m_System;
		FMOD::ChannelGroup* m_Master;
		FMOD::ChannelGroup* m_Groups[CATEGORY_COUNT];
		SoundMap m_Sounds[CATEGORY_COUNT];
		FMOD_MODE m_Modes[CATEGORY_COUNT];
		FMOD::Channel* m_CurrentSong;
		std::string m_CurrentSongPath;
		std::string m_NextSongPath;
		FadeState m_Fade;


	};
}

#endif

#endif
