#include "jspch.h"
#include "Application.h"

#include "Jigsaw/Events/ApplicationEvent.h"
#include "Jigsaw/Log.h"
#include <GLFW/glfw3.h>

namespace Jigsaw {

	Application::Application() {
        m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {
	}

	void Application::Run() {
		while (m_Running) {
            glClearColor(1,0,1,1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
	}

}
