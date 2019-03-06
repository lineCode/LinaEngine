#include <Lina.hpp>



class TestLayer : public LinaEngine::Layer
{
public:

	TestLayer() : Layer("Test")
	{

	}

	void OnUpdate() override
	{
		//LINA_CLIENT_INFO("TestLayer Update");
	}

	void OnEvent(LinaEngine::Event& e) override
	{
		//LINA_CLIENT_TRACE("{0}", e);
	}
};

class Editor : public LinaEngine::Application
{
public:
	Editor() {

		LinaEngine::Layer* l = new TestLayer();

		PushLayer(l);
		PushOverlay(new LinaEngine::ImGuiLayer());
	}
	~Editor() {}


};

LinaEngine::Application* LinaEngine::CreateApplication()
{
	return new Editor();
}