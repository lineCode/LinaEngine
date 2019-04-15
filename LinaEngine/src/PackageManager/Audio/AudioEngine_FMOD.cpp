#include "LinaPch.hpp"

#ifdef LLF_AUDIO_FMOD

#include "AudioEngine_FMOD.hpp"

#include "Lina/Core/Application.hpp"
#include "Lina/Audio/AudioEngine.hpp"

namespace LinaEngine
{

	LinaEngine::AudioEngine_FMOD::AudioEngine_FMOD()
	{
		LINA_CORE_TRACE("[Constructor] -> Audio Engine FMOD ({0})", typeid(*this).name());
	}

	LinaEngine::AudioEngine_FMOD::~AudioEngine_FMOD()
	{
		LINA_CORE_TRACE("[Destructor] -> Audio Engine FMOD ({0})", typeid(*this).name());
	}

	void LinaEngine::AudioEngine_FMOD::Initialize()
	{
		AudioEngine::Initialize();

		LINA_CORE_TRACE("[Initialization] -> Audio Engine FMOD ({0})", typeid(*this).name());
	}

	void LinaEngine::AudioEngine_FMOD::Start()
	{
	}

	void LinaEngine::AudioEngine_FMOD::OnUpdate()
	{
	}

	void LinaEngine::AudioEngine_FMOD::OnEvent(Event & e)
	{
	}

}

#endif