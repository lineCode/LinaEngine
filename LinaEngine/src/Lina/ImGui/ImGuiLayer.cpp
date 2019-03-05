#include "LinaPch.hpp"
#include "ImGuiLayer.hpp"

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_opengl3.h"

#include "SDL.h"
#include <glad/glad.h>

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

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	void ImGuiLayer::OnEvent(Event & event)
	{
	}
}