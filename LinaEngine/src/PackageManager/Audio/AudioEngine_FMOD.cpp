#include "LinaPch.hpp"

#ifdef LLF_AUDIO_FMOD

#include "AudioEngine_FMOD.hpp"

#include "Lina/Core/Application.hpp"
#include "Lina/Audio/AudioEngine.hpp"

#include "Lina/Core/Application.hpp"
#include "Lina/Input/InputEngine.hpp"

#include <GLFW/glfw3.h> // TEMPORARY

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

		// Seed the random number generator for SFXs, that will be used to create random value in a given interval.
		srand(time(0));

		LINA_CORE_TRACE("[Initialization] -> Audio Engine FMOD ({0})", typeid(*this).name());
	}

	void LinaEngine::AudioEngine_FMOD::Start()
	{
		LoadSFX(ResourceConstants::SoundsPath + "jaguar.wav");
		LoadSong(ResourceConstants::SongsPath + "stereo.ogg");
	}

	void LinaEngine::AudioEngine_FMOD::OnUpdate()
	{
		float deltaTime = glfwGetTime();
		this->Update(deltaTime);

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
		if (i.GetKeyDown(LINA_KEY_N))
		{
			PlaySong(ResourceConstants::SongsPath + "stereo.ogg");
		}
		if (i.GetKeyDown(LINA_KEY_M))
		{
			StopSongs();
		}
	}

	void AudioEngine_FMOD::Update(float deltaTime)
	{
		// If a song is playing and the song is FADE_IN mode, increase the volume of the current song little by little.
		// Once the volume reaches 1.0f, stop fading in the volume.

		// If a song is playing and the song is FADE_OUT mode, decrease the volume of the current song little by little.
		// Once the volume reaches 0.0f, stop the song and stop fading out the volume.

		// If no song playing and there is a new song set up to play next, start playing the new song.

		const float fadeTime = 1.0f; // Seconds.
		
		if (m_CurrentSong != 0 && m_Fade == FADE_IN)
		{
			// Store the current volume of the song into a float variable.
			// And then calculate the nextVolume value.
			float volume;
			m_CurrentSong->getVolume(&volume);
			float nextVolume = volume + deltaTime / fadeTime;

			if (nextVolume >= 1.0f)
			{
				m_CurrentSong->setVolume(1.0f);
				m_Fade = FADE_NONE;
			}
			else
			{
				m_CurrentSong->setVolume(nextVolume);
			}
		}
		else if (m_CurrentSong != 0 && m_Fade == FADE_OUT)
		{
			// Store the current volume of the song into a float variable.
			// And then calculate the nextVolume value.
			float volume;
			m_CurrentSong->getVolume(&volume);
			float nextVolume = volume - deltaTime / fadeTime;

			if (nextVolume <= 0.0f)
			{
				m_CurrentSong->stop();
				m_CurrentSong = 0;
				m_CurrentSongPath.clear();
				m_Fade = FADE_NONE;
			}
			else
			{
				m_CurrentSong->setVolume(nextVolume);
			}
		}
		else if (m_CurrentSong == 0 && !m_NextSongPath.empty())
		{
			PlaySong(m_NextSongPath);
			m_NextSongPath.clear();
		}

		m_System->update();
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
		
		// To play the sound, set the channel paused false.
		channel->setPaused(false);
	}

	void AudioEngine_FMOD::PlaySong(const std::string & path)
	{
		// Ignore if this song is already playing.
		if (m_CurrentSongPath == path)
			return;

		// If a song is playing stop it and set this as the next song.
		if (m_CurrentSong != 0)
		{
			StopSongs();
			m_NextSongPath = path;
			return;
		}

		// Find the song in the SoundMap, if the song does not exist return.
		SoundMap::iterator sound = m_Sounds[CATEGORY_SONG].find(path);
		if (sound == m_Sounds[CATEGORY_SONG].end())
			return;

		// Start playing the song with the volume 0 and Fade in.
		m_CurrentSongPath = path;
		m_System->playSound(sound->second, NULL, true, &m_CurrentSong);
		m_CurrentSong->setChannelGroup(m_Groups[CATEGORY_SONG]);
		m_CurrentSong->setVolume(0.0f);
		m_CurrentSong->setPaused(false);
		m_Fade = FADE_IN;
	}

	void AudioEngine_FMOD::StopSFXs()
	{
		// Stop all the sound effects.
		m_Groups[CATEGORY_SFX]->stop();
	}

	void AudioEngine_FMOD::StopSongs()
	{
		// If there is a song that is playing FADE_OUT the song.
		if (m_CurrentSong != 0)
			m_Fade = FADE_OUT;

		// If there is a pending request for to play song clear it.
		m_NextSongPath.clear();
	}

	void AudioEngine_FMOD::SetMasterVolume(float volume)
	{
		m_Master->setVolume(volume);
	}

	void AudioEngine_FMOD::SetSFXsVolume(float volume)
	{
		m_Groups[CATEGORY_SFX]->setVolume(volume);
	}

	void AudioEngine_FMOD::SetSongsVolume(float volume)
	{
		m_Groups[CATEGORY_SONG]->setVolume(volume);
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