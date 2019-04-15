#include "LinaPch.hpp"
#include "AudioEngine.hpp"

namespace LinaEngine
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	LinaEngine::AudioEngine::AudioEngine()
	{
		LINA_CORE_TRACE("[Constructor] -> Audio Engine ({0})", typeid(*this).name());
	}

	AudioEngine::~AudioEngine()
	{
		LINA_CORE_TRACE("[Destructor] -> Audio Engine ({0})", typeid(*this).name());
	}

	void AudioEngine::Initialize()
	{
		LINA_CORE_TRACE("[Initialization] -> Audio Engine ({0})", typeid(*this).name());
	}

	void AudioEngine::OnUpdate()
	{
	}

}