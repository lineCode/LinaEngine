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

		// Release the sounds in each category.
		SoundMap::iterator iter;
		for (int i = 0; i < CATEGORY_COUNT; ++i)
		{
			for (iter = m_Sounds[i].begin(); iter != m_Sounds[i].end(); ++iter)
			{
				iter->second->release();
			}

			m_Sounds[i].clear();
		}

		// Release the system.
		m_System->release();
	}

	void LinaEngine::AudioEngine_FMOD::Initialize()
	{
		AudioEngine::Initialize();

		FMOD::System_Create(&m_System);
		m_System->init(100, FMOD_INIT_NORMAL, 0);

		// Create channels groups for each Category
		m_System->getMasterChannelGroup(&m_Master);
		for (int i = 0; i < CATEGORY_COUNT; ++i)
		{
			m_System->createChannelGroup(0, &m_Groups[i]);
			m_Master->addGroup(m_Groups[i]);
		}

		// Set up modes for each Category
		m_Modes[CATEGORY_SFX] = FMOD_DEFAULT;
		m_Modes[CATEGORY_SONG] = FMOD_DEFAULT | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL;

		// Seed the random number generator for SFXs.
		srand(time(0));

		LINA_CORE_TRACE("[Initialization] -> Audio Engine FMOD ({0})", typeid(*this).name());
	}

	void LinaEngine::AudioEngine_FMOD::Start()
	{
		LoadSFX(ResourceConstants::SoundsPath + "jaguar.wav");
	}

	void LinaEngine::AudioEngine_FMOD::OnUpdate()
	{

		OnInput(app->GetInputEngine());
	}

	void LinaEngine::AudioEngine_FMOD::OnEvent(Event & e)
	{
	}

	void AudioEngine_FMOD::OnInput(InputEngine& i)
	{
		if (i.GetKeyDown(LINA_KEY_B))
		{
			PlaySFX(ResourceConstants::SoundsPath + "jaguar.wav", 0.0f, 1.0f, 20.0f, 2000.0f);
		}
		if (i.GetKeyDown(LINA_KEY_V))
		{
			StopSFXs();
		}
	}

	void AudioEngine_FMOD::LoadSFX(const std::string & path)
	{
		Load(CATEGORY_SFX, path);
	}

	void AudioEngine_FMOD::LoadSong(const std::string & path)
	{
		Load(CATEGORY_SONG, path);
	}

	void AudioEngine_FMOD::PlaySFX(const std::string & path, float minVolume, float maxVolume, float minPitch, float maxPitch)
	{
		// Try to find sound effect and return if not found.
		SoundMap::iterator sound = m_Sounds[CATEGORY_SFX].find(path);
		if (sound == m_Sounds[CATEGORY_SFX].end())
			return;

		// Calculate random volume and pitch in selected range.
		float volume = RandomBetween(minVolume, maxVolume);
		float pitch = RandomBetween(minPitch, maxPitch);

		// Play the sound effect with these initial sound values.
		FMOD::Channel* channel;
		m_System->playSound(sound->second, NULL, true, &channel);
		channel->setChannelGroup(m_Groups[CATEGORY_SFX]);
		channel->setVolume(volume);
		

		// Set the pitch randomly based on Semitone later. 
		//float frequency;
		//channel->getFrequency(&frequency);
		//channel->setFrequency(ChangeSemitone(frequency, pitch));
		
		// After playing the sound, set the channel paused.
		channel->setPaused(false);
	}

	void AudioEngine_FMOD::PlaySong(const std::string & path)
	{
	}

	void AudioEngine_FMOD::StopSFXs()
	{
		// Stop all the sound effects.
		m_Groups[CATEGORY_SFX]->stop();
	}

	void AudioEngine_FMOD::StopSongs()
	{
	}

	void AudioEngine_FMOD::SetMasterVolume(float volume)
	{
	}

	void AudioEngine_FMOD::SetSFXsVolume(float volume)
	{
	}

	void AudioEngine_FMOD::SetSongsVolume(float volume)
	{
	}

	void AudioEngine_FMOD::Load(Category type, const std::string & path)
	{
		// If the requested sound is already in the SoundMap then return.
		if (m_Sounds[type].find(path) != m_Sounds[type].end())
			return;

		// Else create the sound and insert it to the SoundMap.
		FMOD::Sound* sound;
		m_System->createSound(path.c_str(), m_Modes[type], 0, &sound);
		m_Sounds[type].insert(std::make_pair(path, sound));
	}

	float AudioEngine_FMOD::RandomBetween(float min, float max)
	{
		if (min == max)
			return min;

		float n = (float)rand() / (float)RAND_MAX;
		return min + n * (max - min);
	}

	float AudioEngine_FMOD::ChangeOctave(float frequency, float variation)
	{
		static float octave_ratio = 2.0f;
		return frequency * pow(octave_ratio, variation);
	}

	float AudioEngine_FMOD::ChangeSemitone(float frequency, float variation)
	{
		static float semitone_ratio = pow(2.0f, 1.0f / 12.0f);
		return frequency * pow(semitone_ratio, variation);
	}
}

#endif