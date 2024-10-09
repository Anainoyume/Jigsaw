#include "jspch.h"
#include <Jigsaw.h>

class Sandbox : public Jigsaw::Application 
{
public:
	Sandbox() = default;
	~Sandbox() override = default;
};

Jigsaw::Application* Jigsaw::CreateApplication() {
	return new Sandbox();
}