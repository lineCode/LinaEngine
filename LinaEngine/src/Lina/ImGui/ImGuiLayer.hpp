#pragma once

#include "Lina/Layer.hpp"

#include "Lina/Events/ApplicationEvent.hpp"
#include "Lina/Events/KeyEvent.hpp"
#include "Lina/Events/MouseEvent.hpp"

namespace LinaEngine
{
	class LINA_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	};
}
