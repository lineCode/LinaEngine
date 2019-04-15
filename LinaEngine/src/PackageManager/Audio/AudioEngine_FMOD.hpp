#pragma once

#ifdef LLF_AUDIO_FMOD

#ifndef AudioEngine_FMOD_HPP
#define AudioEngine_FMOD_HPP

#include "Lina/Audio/AudioEngine.hpp"

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

	private:
	};
}

#endif

#endif
