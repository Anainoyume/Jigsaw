#include "jspch.h"
#include "Application.h"

#include "Jigsaw/Events/ApplicationEvent.h"
#include "Jigsaw/Log.h"
#include <GLFW/glfw3.h>

namespace Jigsaw {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application() {
        m_Window = std::unique_ptr<Window>(Window::Create());
        // 设置窗口事件回调函数的实现
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    }

	Application::~Application() {

	}

    void Application::OnEvent(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

        JS_CORE_TRACE(e);
    }

	void Application::Run() {
		while (m_Running) {
            glClearColor(1,0,1,1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
	}

    bool Application::OnWindowClose(WindowCloseEvent &e) {
        m_Running = false;
        return true;
    }

}
