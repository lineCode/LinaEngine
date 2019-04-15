#pragma once

#ifdef LLF_AUDIO_FMOD

#ifndef AudioEngine_FMOD_HPP
#define AudioEngine_FMOD_HPP

#include "Lina/Audio/AudioEngine.hpp"

#include <string>
#include <map>
#include <fmod.hpp>

typedef std::map<std::string, FMOD::Sound*> SoundMap;

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

		void Load(const std::string& path);
		void Stream(const std::string& path);
		void Play(const std::string& path);
		void Update();

	private:

		void LoadOrStream(const std::string& path, bool stream);
		FMOD::System* m_System;
		SoundMap m_Sounds;
	};
}

#endif

#endif
