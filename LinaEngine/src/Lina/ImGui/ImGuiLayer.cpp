#include "LinaPch.hpp"
#include "ImGuiLayer.hpp"

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "SDL.h"


namespace LinaEngine
{
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		/*io.KeyMap[ImGuiKey_Tab] = LINA_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = LINA_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = LINA_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = LINA_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = LINA_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = LINA_KEY_PAGEUP;
		io.KeyMap[ImGuiKey_PageDown] = LINA_KEY_PAGEDOWN;
		io.KeyMap[ImGuiKey_Home] = LINA_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = LINA_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = LINA_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = LINA_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = LINA_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = LINA_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = LINA_KEY_RETURN;
		io.KeyMap[ImGuiKey_Escape] = LINA_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = LINA_KEY_A;
		io.KeyMap[ImGuiKey_C] = LINA_KEY_C;
		io.KeyMap[ImGuiKey_V] = LINA_KEY_V;
		io.KeyMap[ImGuiKey_X] = LINA_KEY_X;
		io.KeyMap[ImGuiKey_Y] = LINA_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = LINA_KEY_Z;*/

		ImGui_ImplOpenGL3_Init();
	}

	void ImGuiLayer::OnDetach()
	{
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		//Application& app = Application::Get();
		io.DisplaySize = ImVec2(1280, 720);

		//Temporary deltatime.
		float time = (float)SDL_GetTicks() * 1000;
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(LINA_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(LINA_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(LINA_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(LINA_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(LINA_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(LINA_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(LINA_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent & e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent & e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent & e)
	{
		

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent & e)
	{
	
		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent & e)
	{
	

		return false;
	}
}