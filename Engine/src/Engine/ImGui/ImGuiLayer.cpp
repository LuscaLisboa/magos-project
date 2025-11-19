#include "enginepch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.cpp" 
#include "backends/imgui_impl_opengl3.cpp"

#include "Engine/Application.h"

namespace Engine {

    // namespace {
    //     ImGuiKey GlfwKeyToImGuiKey(int key) {
    //         switch (key) {
    //             case GLFW_KEY_TAB: return ImGuiKey_Tab;
    //             case GLFW_KEY_LEFT: return ImGuiKey_LeftArrow;
    //             case GLFW_KEY_RIGHT: return ImGuiKey_RightArrow;
    //             case GLFW_KEY_UP: return ImGuiKey_UpArrow;
    //             case GLFW_KEY_DOWN: return ImGuiKey_DownArrow;
    //             case GLFW_KEY_PAGE_UP: return ImGuiKey_PageUp;
    //             case GLFW_KEY_PAGE_DOWN: return ImGuiKey_PageDown;
    //             case GLFW_KEY_HOME: return ImGuiKey_Home;
    //             case GLFW_KEY_END: return ImGuiKey_End;
    //             case GLFW_KEY_INSERT: return ImGuiKey_Insert;
    //             case GLFW_KEY_DELETE: return ImGuiKey_Delete;
    //             case GLFW_KEY_BACKSPACE: return ImGuiKey_Backspace;
    //             case GLFW_KEY_SPACE: return ImGuiKey_Space;
    //             case GLFW_KEY_ENTER: return ImGuiKey_Enter;
    //             case GLFW_KEY_ESCAPE: return ImGuiKey_Escape;
    //             case GLFW_KEY_APOSTROPHE: return ImGuiKey_Apostrophe;
    //             case GLFW_KEY_COMMA: return ImGuiKey_Comma;
    //             case GLFW_KEY_MINUS: return ImGuiKey_Minus;
    //             case GLFW_KEY_PERIOD: return ImGuiKey_Period;
    //             case GLFW_KEY_SLASH: return ImGuiKey_Slash;
    //             case GLFW_KEY_SEMICOLON: return ImGuiKey_Semicolon;
    //             case GLFW_KEY_EQUAL: return ImGuiKey_Equal;
    //             case GLFW_KEY_LEFT_BRACKET: return ImGuiKey_LeftBracket;
    //             case GLFW_KEY_BACKSLASH: return ImGuiKey_Backslash;
    //             case GLFW_KEY_RIGHT_BRACKET: return ImGuiKey_RightBracket;
    //             case GLFW_KEY_GRAVE_ACCENT: return ImGuiKey_GraveAccent;
    //             case GLFW_KEY_CAPS_LOCK: return ImGuiKey_CapsLock;
    //             case GLFW_KEY_SCROLL_LOCK: return ImGuiKey_ScrollLock;
    //             case GLFW_KEY_NUM_LOCK: return ImGuiKey_NumLock;
    //             case GLFW_KEY_PRINT_SCREEN: return ImGuiKey_PrintScreen;
    //             case GLFW_KEY_PAUSE: return ImGuiKey_Pause;
    //             case GLFW_KEY_KP_DECIMAL: return ImGuiKey_KeypadDecimal;
    //             case GLFW_KEY_KP_DIVIDE: return ImGuiKey_KeypadDivide;
    //             case GLFW_KEY_KP_MULTIPLY: return ImGuiKey_KeypadMultiply;
    //             case GLFW_KEY_KP_SUBTRACT: return ImGuiKey_KeypadSubtract;
    //             case GLFW_KEY_KP_ADD: return ImGuiKey_KeypadAdd;
    //             case GLFW_KEY_KP_ENTER: return ImGuiKey_KeypadEnter;
    //             case GLFW_KEY_KP_EQUAL: return ImGuiKey_KeypadEqual;
    //             case GLFW_KEY_LEFT_SHIFT: return ImGuiKey_LeftShift;
    //             case GLFW_KEY_LEFT_CONTROL: return ImGuiKey_LeftCtrl;
    //             case GLFW_KEY_LEFT_ALT: return ImGuiKey_LeftAlt;
    //             case GLFW_KEY_LEFT_SUPER: return ImGuiKey_LeftSuper;
    //             case GLFW_KEY_RIGHT_SHIFT: return ImGuiKey_RightShift;
    //             case GLFW_KEY_RIGHT_CONTROL: return ImGuiKey_RightCtrl;
    //             case GLFW_KEY_RIGHT_ALT: return ImGuiKey_RightAlt;
    //             case GLFW_KEY_RIGHT_SUPER: return ImGuiKey_RightSuper;
    //             case GLFW_KEY_MENU: return ImGuiKey_Menu;
    //             default:
    //                 break;
    //         }
    //
    //         if (key >= GLFW_KEY_0 && key <= GLFW_KEY_9)
    //             return static_cast<ImGuiKey>(ImGuiKey_0 + (key - GLFW_KEY_0));
    //         if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z)
    //             return static_cast<ImGuiKey>(ImGuiKey_A + (key - GLFW_KEY_A));
    //         if (key >= GLFW_KEY_F1 && key <= GLFW_KEY_F25)
    //             return static_cast<ImGuiKey>(ImGuiKey_F1 + (key - GLFW_KEY_F1));
    //         if (key >= GLFW_KEY_KP_0 && key <= GLFW_KEY_KP_9)
    //             return static_cast<ImGuiKey>(ImGuiKey_Keypad0 + (key - GLFW_KEY_KP_0));

    //         return ImGuiKey_None;
    //     }
    // }

    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer"){
    
    }

    ImGuiLayer::~ImGuiLayer() {

    }

    static void glfw_error_callback(int error, const char* description){
        fprintf(stderr, "GLFW Error %d: %s\n", error, description);
    }

    void ImGuiLayer::OnAttach() {
        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit())
            return;

        // Decide GL+GLSL versions
    #if defined(IMGUI_IMPL_OPENGL_ES2)
        // GL ES 2.0 + GLSL 100 (WebGL 1.0)
        const char* glsl_version = "#version 100";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    #elif defined(IMGUI_IMPL_OPENGL_ES3)
        // GL ES 3.0 + GLSL 300 es (WebGL 2.0)
        const char* glsl_version = "#version 300 es";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    #elif defined(__APPLE__)
        // GL 3.2 + GLSL 150
        const char* glsl_version = "#version 150";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
    #else
        // GL 3.0 + GLSL 130
        const char* glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
    #endif

        // Create window with graphics context
        float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only
        GLFWwindow* window = glfwCreateWindow((int)(1280 * main_scale), (int)(800 * main_scale), "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
        if (window == nullptr)
            return;
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Enable vsync
        
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Setup scaling
        ImGuiStyle& style = ImGui::GetStyle();
        style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
        style.FontScaleDpi = main_scale;        // Set initial font scale. (using io.ConfigDpiScaleFonts=true makes this unnecessary. We leave both here for documentation purpose)
    #if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        io.ConfigDpiScaleFonts = true;          // [Experimental] Automatically overwrite style.FontScaleDpi in Begin() when Monitor DPI changes. This will scale fonts but _NOT_ scale sizes/padding for now.
        io.ConfigDpiScaleViewports = true;      // [Experimental] Scale Dear ImGui and Platform Windows when Monitor DPI changes.
    #endif

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
    #ifdef __EMSCRIPTEN__
        ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
    #endif
        ImGui_ImplOpenGL3_Init(glsl_version);

        // Load Fonts
        // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
        // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
        // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
        // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
        // - Read 'docs/FONTS.md' for more instructions and details. If you like the default font but want it to scale better, consider using the 'ProggyVector' from the same author!
        // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
        // - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
        //style.FontSizeBase = 20.0f;
        //io.Fonts->AddFontDefault();
        //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf");
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf");
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf");
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf");
        //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf");
        //IM_ASSERT(font != nullptr);

        // Our state
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    }
    
    void ImGuiLayer::OnDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::Begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End() {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize= ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void ImGuiLayer::OnImGuiRender() {
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }
}