#pragma once

#ifdef JS_PLATFORM_WINDOWS

extern Jigsaw::Application* Jigsaw::CreateApplication();

int main(int argc, char** argv) {
	auto app = Jigsaw::CreateApplication();
	app->Run();
	delete app;
}

#endif
