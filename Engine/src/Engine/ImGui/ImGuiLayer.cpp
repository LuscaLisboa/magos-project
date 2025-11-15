#include "enginepch.h"
#include "ImGuiLayer.h"

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>

#include "Engine/Application.h"

namespace Engine {

    namespace {
        ImGuiKey GlfwKeyToImGuiKey(int key) {
            switch (key) {
                case GLFW_KEY_TAB: return ImGuiKey_Tab;
                case GLFW_KEY_LEFT: return ImGuiKey_LeftArrow;
                case GLFW_KEY_RIGHT: return ImGuiKey_RightArrow;
                case GLFW_KEY_UP: return ImGuiKey_UpArrow;
                case GLFW_KEY_DOWN: return ImGuiKey_DownArrow;
                case GLFW_KEY_PAGE_UP: return ImGuiKey_PageUp;
                case GLFW_KEY_PAGE_DOWN: return ImGuiKey_PageDown;
                case GLFW_KEY_HOME: return ImGuiKey_Home;
                case GLFW_KEY_END: return ImGuiKey_End;
                case GLFW_KEY_INSERT: return ImGuiKey_Insert;
                case GLFW_KEY_DELETE: return ImGuiKey_Delete;
                case GLFW_KEY_BACKSPACE: return ImGuiKey_Backspace;
                case GLFW_KEY_SPACE: return ImGuiKey_Space;
                case GLFW_KEY_ENTER: return ImGuiKey_Enter;
                case GLFW_KEY_ESCAPE: return ImGuiKey_Escape;
                case GLFW_KEY_APOSTROPHE: return ImGuiKey_Apostrophe;
                case GLFW_KEY_COMMA: return ImGuiKey_Comma;
                case GLFW_KEY_MINUS: return ImGuiKey_Minus;
                case GLFW_KEY_PERIOD: return ImGuiKey_Period;
                case GLFW_KEY_SLASH: return ImGuiKey_Slash;
                case GLFW_KEY_SEMICOLON: return ImGuiKey_Semicolon;
                case GLFW_KEY_EQUAL: return ImGuiKey_Equal;
                case GLFW_KEY_LEFT_BRACKET: return ImGuiKey_LeftBracket;
                case GLFW_KEY_BACKSLASH: return ImGuiKey_Backslash;
                case GLFW_KEY_RIGHT_BRACKET: return ImGuiKey_RightBracket;
                case GLFW_KEY_GRAVE_ACCENT: return ImGuiKey_GraveAccent;
                case GLFW_KEY_CAPS_LOCK: return ImGuiKey_CapsLock;
                case GLFW_KEY_SCROLL_LOCK: return ImGuiKey_ScrollLock;
                case GLFW_KEY_NUM_LOCK: return ImGuiKey_NumLock;
                case GLFW_KEY_PRINT_SCREEN: return ImGuiKey_PrintScreen;
                case GLFW_KEY_PAUSE: return ImGuiKey_Pause;
                case GLFW_KEY_KP_DECIMAL: return ImGuiKey_KeypadDecimal;
                case GLFW_KEY_KP_DIVIDE: return ImGuiKey_KeypadDivide;
                case GLFW_KEY_KP_MULTIPLY: return ImGuiKey_KeypadMultiply;
                case GLFW_KEY_KP_SUBTRACT: return ImGuiKey_KeypadSubtract;
                case GLFW_KEY_KP_ADD: return ImGuiKey_KeypadAdd;
                case GLFW_KEY_KP_ENTER: return ImGuiKey_KeypadEnter;
                case GLFW_KEY_KP_EQUAL: return ImGuiKey_KeypadEqual;
                case GLFW_KEY_LEFT_SHIFT: return ImGuiKey_LeftShift;
                case GLFW_KEY_LEFT_CONTROL: return ImGuiKey_LeftCtrl;
                case GLFW_KEY_LEFT_ALT: return ImGuiKey_LeftAlt;
                case GLFW_KEY_LEFT_SUPER: return ImGuiKey_LeftSuper;
                case GLFW_KEY_RIGHT_SHIFT: return ImGuiKey_RightShift;
                case GLFW_KEY_RIGHT_CONTROL: return ImGuiKey_RightCtrl;
                case GLFW_KEY_RIGHT_ALT: return ImGuiKey_RightAlt;
                case GLFW_KEY_RIGHT_SUPER: return ImGuiKey_RightSuper;
                case GLFW_KEY_MENU: return ImGuiKey_Menu;
                default:
                    break;
            }

            if (key >= GLFW_KEY_0 && key <= GLFW_KEY_9)
                return static_cast<ImGuiKey>(ImGuiKey_0 + (key - GLFW_KEY_0));
            if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z)
                return static_cast<ImGuiKey>(ImGuiKey_A + (key - GLFW_KEY_A));
            if (key >= GLFW_KEY_F1 && key <= GLFW_KEY_F25)
                return static_cast<ImGuiKey>(ImGuiKey_F1 + (key - GLFW_KEY_F1));
            if (key >= GLFW_KEY_KP_0 && key <= GLFW_KEY_KP_9)
                return static_cast<ImGuiKey>(ImGuiKey_Keypad0 + (key - GLFW_KEY_KP_0));

            return ImGuiKey_None;
        }
    }

    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer"){
    
    }

    ImGuiLayer::~ImGuiLayer() {

    }

    void ImGuiLayer::OnAttach() {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        io.BackendPlatformName = "MagosEngine-GLFW";
        io.BackendRendererName = "MagosEngine-OpenGL";

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnUpdate() {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        float time = (float)glfwGetTime();
        io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
        m_Time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(Event& event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseButtonPressedEvent>(ENGINE_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(ENGINE_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
        dispatcher.Dispatch<MouseMovedEvent>(ENGINE_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(ENGINE_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
        dispatcher.Dispatch<KeyPressedEvent>(ENGINE_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(ENGINE_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<KeyTypedEvent>(ENGINE_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
        dispatcher.Dispatch<WindowResizeEvent>(ENGINE_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
    }

    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = true;

        return false;
    }

    bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = false;

        return false;
    }

    bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(e.GetX(), e.GetY());

        return false;
    }

    bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += e.GetXOffset();
        io.MouseWheel += e.GetYOffset();

        return false;
    }

    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        int key = e.GetKeyCode();
        
        ImGuiKey imguiKey = GlfwKeyToImGuiKey(key);
        if(imguiKey != ImGuiKey_None) {
            io.AddKeyEvent(imguiKey, true);
            io.SetKeyEventNativeData(imguiKey, key, key);
        }

        switch (key) {
            case GLFW_KEY_LEFT_CONTROL:
                m_LeftCtrlPressed = true;
                break;
            case GLFW_KEY_RIGHT_CONTROL:
                m_RightCtrlPressed = true;
                break;
            case GLFW_KEY_LEFT_SHIFT:
                m_LeftShiftPressed = true;
                break;
            case GLFW_KEY_RIGHT_SHIFT:
                m_RightShiftPressed = true;
                break;
            case GLFW_KEY_LEFT_ALT:
                m_LeftAltPressed = true;
                break;
            case GLFW_KEY_RIGHT_ALT:
                m_RightAltPressed = true;
                break;
            case GLFW_KEY_LEFT_SUPER:
                m_LeftSuperPressed = true;
                break;
            case GLFW_KEY_RIGHT_SUPER:
                m_RightSuperPressed = true;
                break;
            default:
                break;
        }

        UpdateModifierKeys(io);

        return false;
    }

    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        int key = e.GetKeyCode();

        ImGuiKey imguiKey = GlfwKeyToImGuiKey(key);
        if (imguiKey != ImGuiKey_None) {
            io.AddKeyEvent(imguiKey, false);
            io.SetKeyEventNativeData(imguiKey, key, key);
        }

        switch (key) {
            case GLFW_KEY_LEFT_CONTROL:
                m_LeftCtrlPressed = false;
                break;
            case GLFW_KEY_RIGHT_CONTROL:
                m_RightCtrlPressed = false;
                break;
            case GLFW_KEY_LEFT_SHIFT:
                m_LeftShiftPressed = false;
                break;
            case GLFW_KEY_RIGHT_SHIFT:
                m_RightShiftPressed = false;
                break;
            case GLFW_KEY_LEFT_ALT:
                m_LeftAltPressed = false;
                break;
            case GLFW_KEY_RIGHT_ALT:
                m_RightAltPressed = false;
                break;
            case GLFW_KEY_LEFT_SUPER:
                m_LeftSuperPressed = false;
                break;
            case GLFW_KEY_RIGHT_SUPER:
                m_RightSuperPressed = false;
                break;
            default:
                break;
        }

        UpdateModifierKeys(io);

        return false;
    }

    bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        int keycode = e.GetKeyCode();
        if(keycode > 0 && keycode < 0x10000)
            io.AddInputCharacter((unsigned short)keycode);

        return false;
    }

    bool Engine::ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

        glViewport(0, 0, e.GetWidth(), e.GetHeight());

        return false;
    }

    void ImGuiLayer::UpdateModifierKeys(ImGuiIO& io) {
        const bool ctrl  = m_LeftCtrlPressed  || m_RightCtrlPressed;
        const bool shift = m_LeftShiftPressed || m_RightShiftPressed;
        const bool alt   = m_LeftAltPressed   || m_RightAltPressed;
        const bool super = m_LeftSuperPressed || m_RightSuperPressed;

        io.KeyCtrl  = ctrl;
        io.KeyShift = shift;
        io.KeyAlt   = alt;
        io.KeySuper = super;

        #ifdef ImGuiKey_ModCtrl
            io.AddKeyEvent(ImGuiKey_ModCtrl,  ctrl);
            io.AddKeyEvent(ImGuiKey_ModShift, shift);
            io.AddKeyEvent(ImGuiKey_ModAlt,   alt);
            io.AddKeyEvent(ImGuiKey_ModSuper, super);
        #endif
    }   

}