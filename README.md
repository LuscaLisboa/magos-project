# magos-project v0.1.0
Magos Game Engine :p

Magos is a modular C++ engine split into two independent subprojects: a core `Engine` library and a client application `Sandbox`. They communicate via a DLL, allowing `Sandbox` to consume the services exposed by `Engine`. Precompiled headers are set up via `Engine/src/enginepch.h` (and the corresponding `.cpp`).

## Project Structure

- **Subprojects**
  - `Engine/`: core library exported as a DLL.
  - `Sandbox/`: demo executable that links against the DLL.
- **Submodules**
  - [`spdlog`](https://github.com/gabime/spdlog): shared logging for the engine and clients.
  - [`glfw`](https://github.com/glfw/glfw): window creation and input.
- **Build**
  - Managed with CMake (projects, compilation, DLL/executable linkage).
  - `engine_config.json`: configuration used by the engine at runtime.
  - Precompiled header: `Engine/src/enginepch.h`.
- **Main Code Layout**
  - `Engine/src/Application.cpp`: application lifecycle implementation.
  - `Engine/src/Engine/Log.cpp`: centralized logger initialization.
  - Build defines: `ENGINE_BUILD`, `ENGINE_DLL`.
  - `Sandbox/src/SandboxApp.cpp`: sample app entry point.

## Technical Documentation

### Shared Headers

- `Engine.h`: aggregates common headers shared by Engine and Sandbox.
- `Engine/Application.h`: declares `Application`, its lifecycle (`Application::Application`, `~Application`, `Run`), and `Application* CreateApplication()`.
- `Engine/Core.h`: macros for `dllexport` / `dllimport`.

### Implementations

- `Engine/Application.h/.cpp`:
  - `Application`: creates `m_Window` via `Window::Create()`, wires the event callback to `OnEvent()`, controls `m_Running`.
  - `~Application`: releases/shuts down resources.
  - `PushLayer`: pushes a regular layer onto the stack.
  - `PushOverlay`: pushes an overlay (rendered after layers).
  - `OnEvent`: uses `EventDispatcher` for window close; forwards events to layers/overlays (reverse order).
  - `Run`: main loop; sets required GL state (if applicable), calls `m_Window->OnUpdate()` and updates layers.
  - `OnWindowClose`: sets `m_Running = false` and returns `true`.

#### Entry Point
- `Engine/EntryPoint.h`: initializes logging, instantiates the app via `CreateApplication()`, runs it, and destroys it.

#### Logs
- `EngineAPI/Log.h/.cpp`: `s_CoreLogger`, `s_ClientLogger`.

#### Events
- `EngineAPI/Event.h`: event types, categories, helper macros, base `Event`, `EventDispatcher`, and `operator<<`.
- `EngineAPI/ApplicationEvent.h`: `WindowResizeEvent`, `WindowCloseEvent`, `AppTickEvent`, `AppUpdateEvent`, `AppRendererEvent`.
- `EngineAPI/KeyEvent.h`: `KeyEvent`, `KeyPressedEvent` (use `GetRepeatCount()`), `KeyReleasedEvent`.
- `EngineAPI/MouseEvents.h`:
  - `MouseMovedEvent`: stores mouse position (`m_MouseX`, `m_MouseY`), getters `GetX()`, `GetY()`. `ToString()` prints `"MouseMovedEvent: x, y"`. `EVENT_CLASS_TYPE(MouseMoved)`, category `EventCategoryMouse | EventCategoryInput`.
  - `MouseScrolledEvent`: stores scroll offsets (`m_XOffset`, `m_YOffset`), getters `GetXOffset()`, `GetYOffset()`. `ToString()` prints `"MouseScrolledEvent: xOffset, yOffset"`. `EVENT_CLASS_TYPE(MouseScrolled)`, category `EventCategoryMouse | EventCategoryInput`.
  - `MouseButtonEvent` (base): stores button (`m_Button`), getter `GetMouseButton()`. Category `EventCategoryMouse | EventCategoryInput`.
  - `MouseButtonPressedEvent`: `ToString()` → `"MouseButtonPressedEvent: <button>"`. `EVENT_CLASS_TYPE(MouseButtonPressed)`.
  - `MouseButtonReleasedEvent`: `ToString()` → `"MouseButtonReleasedEvent: <button>"`. `EVENT_CLASS_TYPE(MouseButtonReleased)`.

#### Window
- `Engine/Platform/Windows/WindowsWindow.h/.cpp`:
  - Initializes GLFW, creates the window, sets the user pointer, maps GLFW callbacks to engine events.
  - `OnUpdate()` calls `glfwPollEvents()` and `glfwSwapBuffers()`.
  - `SetVSync()` uses `glfwSwapInterval(...)`.

#### Layer
- `EngineAPI/Layer.h/.cpp`:
  - `Layer`, `~Layer`.
  - Virtuals: `OnAttach`, `OnDetach`, `OnUpdate`, `OnEvent`.
- `EngineAPI/LayerStack.h/.cpp`:
  - `LayerStack` constructor/destructor (owns layers).
  - Push APIs: `PushLayer`, `PushOverlay`.
  - Pop APIs: `PopLayer`, `PopOverlay`.

- `Sandbox/SandboxApp.cpp`: derives from `Application` and implements `CreateApplication()`.

## Include Directories
- Added to the Engine target:
  - `Engine/src`
  - `Engine/src/Engine`
  - `Engine/vendor/spdlog/include`
  - `Engine/vendor/glfw/include`
  - _(remove invalid paths like engine “Events” folders or `glfw/src` from include dirs)_

## Implementation Checklist

- [x] Initial setup (CMake, submodules, logging).
- [ ] Render a triangle (window opens, triangle visible, no GL errors).
- [ ] Render a quad.
- [ ] Render a cube.
- [ ] Apply rotation at a steady 60 FPS.
- [ ] Render multiple objects.
- [ ] Add debugging.
- [ ] Implement lighting.
- [ ] Render text.
- [ ] Render particles.
- [ ] Optimize with batched rendering without flicker.

## Learning Track

- GitHub Project Board.
- Branch naming conventions.
- CMake + unit tests (GoogleTest).
- Centralized logging.
- C++17/20 coding guidelines.
- Additional engine topics: graphics math, input systems, ECS, asset pipeline, profiling.
