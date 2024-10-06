#include "jspch.h"
#include "Application.h"

#include "Jigsaw/Events/ApplicationEvent.h"
#include "Jigsaw/Log.h"

namespace Jigsaw {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run() {
		WindowResizeEvent e(1200, 720);
		JS_TRACE(e);

		while (true);
	}

}
