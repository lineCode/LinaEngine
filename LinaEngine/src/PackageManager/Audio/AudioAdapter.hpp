#pragma once
#ifndef AudioAdapter_HPP
#define AudioAdapter_HPP

#ifdef LLF_AUDIO_FMOD

#include "AudioEngine_FMOD.hpp"

#define AUDIO_ENGINE_CREATEFUNC(PARAM) inline AudioEngine* CreateAudioEngine() {return new AudioEngine_FMOD();}

#else

#include "Lina/Audio/AudioEngine.hpp"

#define AUDIO_ENGINE_CREATEFUNC(PARAM) inline AudioEngine* CreateAudioEngine() {LINA_CORE_ERR("No LLF is defined for audio! Aborting!"); exit(EXIT_FAILURE); };

#endif

namespace LinaEngine
{
	class AudioAdapter
	{
	public:
		AudioAdapter() {};
		~AudioAdapter() {};
		AUDIO_ENGINE_CREATEFUNC(PARAM);
	};
}

#endif