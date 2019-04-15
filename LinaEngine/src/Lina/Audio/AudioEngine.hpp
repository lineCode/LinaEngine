#pragma once
#ifndef AudioEngine_HPP
#define AudioEngine_HPP

#include "Lina/Core/Core.hpp"

namespace LinaEngine
{
	class LINA_API AudioEngine
	{
	public:
		virtual ~AudioEngine();

		/* Initializes the audioEngine.  */
		virtual void Initialize();

		/* Starts the audioEngine.  */
		virtual void Start() = 0;

		/* Called in each frame.  */
		virtual void OnUpdate();

		/* Called when an event occurs.  */
		virtual void OnEvent(class Event& e) = 0;

		/* Sets the application reference.  */
		FORCEINLINE void SetApplication(class Application& p)
		{
			LINA_CORE_ASSERT(&p, "Application is nullptr!");
			this->app = &p;
		}

	protected:
		AudioEngine();

		class Application* app;
	};
}

#endif
