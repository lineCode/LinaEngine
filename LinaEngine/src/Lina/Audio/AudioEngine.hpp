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

		virtual void Initialize();

		virtual void Start() = 0;

		virtual void OnUpdate();

		virtual void OnEvent(class Event& e) = 0;

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
