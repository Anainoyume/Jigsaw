#pragma once

#include "Jigsaw/Layer.h"

namespace Jigsaw {

    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event& e) override;
    private:
    };

}
