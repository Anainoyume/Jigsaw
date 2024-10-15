#include "jspch.h"
#include <Jigsaw.h>

class ExampleLayer : public Jigsaw::Layer
{
public:
    ExampleLayer()
        : Layer("Example") {}

    void OnUpdate() override {
        JS_INFO("ExampleLayer::Update");
    }

    void OnEvent(Jigsaw::Event& event) override {
        JS_TRACE("{}", event);
    }
};

class Sandbox : public Jigsaw::Application 
{
public:
	Sandbox() {
        PushLayer(new ExampleLayer());
    }
	~Sandbox() override = default;
};

Jigsaw::Application* Jigsaw::CreateApplication() {
	return new Sandbox();
}