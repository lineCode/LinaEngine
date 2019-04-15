#include "LinaPch.hpp"

#ifdef LLF_AUDIO_FMOD

#include "AudioEngine_FMOD.hpp"

#include "Lina/Core/Application.hpp"
#include "Lina/Audio/AudioEngine.hpp"

#include "Lina/Core/Application.hpp"
#include "Lina/Input/InputEngine.hpp"

namespace LinaEngine
{

	LinaEngine::AudioEngine_FMOD::AudioEngine_FMOD()
	{
		LINA_CORE_TRACE("[Constructor] -> Audio Engine FMOD ({0})", typeid(*this).name());
	}

	LinaEngine::AudioEngine_FMOD::~AudioEngine_FMOD()
	{
		LINA_CORE_TRACE("[Destructor] -> Audio Engine FMOD ({0})", typeid(*this).name());

		SoundMap::iterator iter;
		for (iter = m_Sounds.begin(); iter != m_Sounds.end(); iter++)
		{
			iter->second->release();
		}

		m_Sounds.clear();

		m_System->release();
		m_System = nullptr;
	}

	void LinaEngine::AudioEngine_FMOD::Initialize()
	{
		AudioEngine::Initialize();

		LINA_CORE_TRACE("[Initialization] -> Audio Engine FMOD ({0})", typeid(*this).name());

		FMOD::System_Create(&m_System);
		m_System->init(100, FMOD_INIT_NORMAL, 0);
	}

	void LinaEngine::AudioEngine_FMOD::Start()
	{
		Load(ResourceConstants::SoundsPath + "jaguar.wav");
	}

	void LinaEngine::AudioEngine_FMOD::OnUpdate()
	{
		Update();

		OnInput(app->GetInputEngine());
	}

	void LinaEngine::AudioEngine_FMOD::OnEvent(Event & e)
	{

	}

	void AudioEngine_FMOD::OnInput(InputEngine& i)
	{
		if (i.GetKey(LINA_KEY_B))
		{
			Play(ResourceConstants::SoundsPath + "jaguar.wav");
		}
	}

	void AudioEngine_FMOD::Load(const std::string & path)
	{
		LoadOrStream(path, false);
	}

	void AudioEngine_FMOD::Stream(const std::string & path)
	{
		LoadOrStream(path, true);
	}

	void AudioEngine_FMOD::Play(const std::string & path)
	{
		// Search if there is a matching sound in the SoundMap
		SoundMap::iterator sound = m_Sounds.find(path);

		// Ignore the function call if there is no sound
		if (sound == m_Sounds.end())
			return;

		// Otherwise play the sound.
		m_System->playSound(sound->second, NULL, false, 0);
	}

	void AudioEngine_FMOD::Update()
	{
		m_System->update();
	}

	void AudioEngine_FMOD::LoadOrStream(const std::string & path, bool stream)
	{
		// Ignore the function call if the sound is already loaded.
		if (m_Sounds.find(path) != m_Sounds.end())
			return;

		// Load or stream file into a sound object.
		FMOD::Sound* sound;
		if (stream)
		{
			m_System->createStream(path.c_str(), FMOD_DEFAULT, 0, &sound);
		}
		else
		{
			m_System->createSound(path.c_str(), FMOD_DEFAULT, 0, &sound);
		}

		m_Sounds.insert(std::make_pair(path, sound));
	}

}

#endif