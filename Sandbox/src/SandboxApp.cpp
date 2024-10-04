#include <Jigsaw.h>

class Sandbox : public Jigsaw::Application 
{
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Jigsaw::Application* Jigsaw::CreateApplication() {
	return new Sandbox();
}