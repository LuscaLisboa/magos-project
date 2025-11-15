#pragma once

#include "Engine/Layer.h"

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvents.h"

struct ImGuiIO;

namespace Engine {

    class ENGINE_API ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(Event& event);

    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrolledEvent(MouseScrolledEvent& e);
        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);
        bool OnKeyTypedEvent(KeyTypedEvent& e);
        bool OnWindowResizeEvent(WindowResizeEvent& e);

        void UpdateModifierKeys(ImGuiIO& io);

        float m_Time = 0.0f;

        bool m_LeftCtrlPressed = false;
        bool m_RightCtrlPressed = false;
        bool m_LeftShiftPressed = false;
        bool m_RightShiftPressed = false;
        bool m_LeftAltPressed = false;
        bool m_RightAltPressed = false;
        bool m_LeftSuperPressed = false;
        bool m_RightSuperPressed = false;
    };   

}