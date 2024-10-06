#pragma once

#ifdef JS_PLATFORM_WINDOWS

extern Jigsaw::Application* Jigsaw::CreateApplication();

int main(int argc, char** argv) {
	Jigsaw::Log::Init();
	JS_CORE_WARN("Initialized Log!");
	int a = 5;
	JS_INFO("Hello! Var={0}", a);

	auto app = Jigsaw::CreateApplication();
	app->Run();
	delete app;
}

#endif
