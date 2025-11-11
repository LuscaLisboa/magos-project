# magos-project v0.1.0
Magos Game Engine :p 

Magos é uma engine modular em C++ dividida em dois subprojetos independentes: uma biblioteca "Engine" e uma aplicação cliente "Sandbox". A comunicação ocorre via DLL, permitindo que a Sandbox consuma os serviços expostos pela Engine.

## Estrutura do Projeto

- **Subprojetos**
  - `Engine/`: biblioteca core exportada como DLL.
  - `Sandbox/`: executável de demonstração que consome a DLL.
- **Submódulos**
  - [`spdlog`](https://github.com/gabime/spdlog): logging compartilhado entre engine e clientes.
- **Build**
  - Gerenciado via CMake (criação de projetos, compilação e linkagem da DLL e do executável).
  - `engine_config.json`: define configurações usadas para carregar a DLL.
- **Organização de código principal**
  - `Engine/src/Application.cpp`: implementação do ciclo de vida da aplicação.
  - `Engine/src/Engine/Log.cpp`: inicialização centralizada do logger.
  - Diretórios de include expostos: `Engine/src`, `Engine`, `Engine/vendor/spdlog/include`, `Engine/vendor/Engine/Events`.
  - Definições de compilação: `ENGINE_BUILD`, `ENGINE_DLL`.
  - `Sandbox/src/SandboxApp.cpp`: ponto de entrada da aplicação de teste.

## Documentação Técnica

### Cabeçalhos Compartilhados
- `Engine.h`: agrega os headers comuns entre Engine e Sandbox.
- `Engine/Application.h`: declarações de `Application`, ciclo de vida (`Application::Application`, `~Application`, `Run`) e `Application* CreateApplication()`.
- `Engine/Core.h`: macros para `dllexport` / `dllimport`.

### Implementações
- `Engine/Application.cpp`: define construtor, destrutor e loop principal (`while (true)` em `Application::Run`).
- `Engine/EntryPoint.h`: inicializa logging, instancia a aplicação via `CreateApplication()`, executa `Run()` e desaloca.
- `EngineAPI/Log.h` e `EngineAPI/Log.cpp`: singletons `s_CoreLogger`, `s_ClientLogger`, configuração de pattern e mensagem inicial.
- `EngineAPI`/`Event.h`: sistema base de eventos:
  - enum class `EventType` com todos os tipos (janela, app, teclado, mouse).
  - enum `EventCategory` com flags de categoria (`EventCategoryApplication`, `EventCategoryInput`, etc.).
  - Macros `EVENT_CLASS_TYPE` e `EVENT_CLASS_CATEGORY` para padronizar tipo/nome/categorias nas classes derivadas.
  - Classe abstrata `Event` com `GetEventType()`, `GetName()`, `GetCategoryFlags()`, `ToString()` e flag `m_Handled`.
  - Método ``IsInCategory`` para checar categorias via bitmask.
  - ``EventDispatcher`` para despachar um ``Event`` para handlers tipados usando ``GetStaticType()``.
  - ``operator<<`` para logar eventos via ``ToString()``.
- `EngineAPI/ApplicationEvent.h`: eventos de nível de aplicação que herdam de Event:
  - WindowResizeEvent
    - Construtor recebe ``width`` e ``height``.
    - Membros ``m_Width``, ``m_Height``, getters ``GetWidth()``, ``GetHeight()``.
    - ``ToString()`` formatando "``WindowResizeEvent``: ``width``, ``height``".
    - Usa ``EVENT_CLASS_TYPE(WindowResize)`` e ``EVENT_CLASS_CATEGORY(EventCategoryApplication)``.
  - ``WindowCloseEvent``
    - Sem dados adicionais.
    - Usa ``EVENT_CLASS_TYPE(WindowClose)`` e ``EVENT_CLASS_CATEGORY(EventCategoryApplication)``.
  - ``AppTickEvent``
    - Representa o tick da aplicação.
    - Usa ``EVENT_CLASS_TYPE(AppTick)`` e ``EVENT_CLASS_CATEGORY(EventCategoryApplication)``.
  - ``AppUpdateEvent``
    - Representa o update da aplicação.
    - Usa ``EVENT_CLASS_TYPE(AppUpdate)`` e ``EVENT_CLASS_CATEGORY(EventCategoryApplication)``.
  - ``AppRendererEvent``
    - Representa o ciclo de renderização da aplicação.
    - Usa ``EVENT_CLASS_TYPE(AppRenderer)`` e ``EVENT_CLASS_CATEGORY(EventCategoryApplication)``.
  - ``EngineAPI``/``KeyEvent.h``:
    - Classe base ``KeyEvent``:
      - Armazena o código da tecla (``m_KeyCode``), fornece ``GetKeyCode()``.
      - Marca categoria como ``EventCategoryKeyboard`` | ``EventCategoryInput``.
    - ``KeyPressedEvent``:
      - Herda de ``KeyEvent``.
      - Armazena contagem de repetição (``m_RepeatCount``), acessível via ``GetrepeatCount()``.
      - ``ToString()`` retorna "`KeyPressedEvent`: ``<key> (<count> repeats)``".
      - Usa ``EVENT_CLASS_TYPE(KeyPressed)``.
    - ``KeyReleasedEvent``:
      - Herda de ``KeyEvent``.
      - ``ToString()`` retorna "``KeyReleasedEvent: <key>``".
      - Usa ``EVENT_CLASS_TYPE(KeyReleased)``.
  - ``EngineAPI``/``MouseEvents.h``:
    - ``MouseMovedEvent``:
      - Guarda posição do mouse (``m_MouseX``, m_MouseY), getters ``GetX()``, ``GetY()``.
      - ``ToString()`` retorna "``MouseMovedEvent: x, y``".
      - ``EVENT_CLASS_TYPE(MouseMoved)`` e categoria ``EventCategoryMouse | EventCategoryInput``.
    - ``MouseScrolledEvent``:
      - Guarda offsets de scroll (``m_XOffset``, ``m_YOffset``), getters ``GetXOffset()``, ``GetYOffset()``.
      - ``ToString()`` retorna "``MouseScrolledEvent: xOffset, yOffset``".
      - ``EVENT_CLASS_TYPE(MouseScrolled)`` e categoria ``EventCategoryMouse | EventCategoryInput``.
    - Classe base ``MouseButtonEvent``:
      - Guarda botão (``m_Button``), getter ``GetMouseButton()``.
      - Categoria ``EventCategoryMouse | EventCategoryInput``.
    - ``MouseButtonPressedEvent``:
      - Herda de ``MouseButtonEvent``.
      - ``ToString()`` retorna "``MouseButtonPressedEvent: <button>``".
      - ``EVENT_CLASS_TYPE(MouseButtonPressed)``.
    - ``MouseButtonReleasedEvent``:
      - Herda de ``MouseButtonEvent``.
      - ``ToString()`` retorna "``MouseButtonReleasedEvent: <button>``".
      - ``EVENT_CLASS_TYPE(MouseButtonReleased)``.
- ``Sandbox``/``SandboxApp.cpp``:
  - Define a classe ``Sandbox`` herdando de ``Engine::Application``.
  - Implementa construtor/destrutor específicos do sandbox.
  - Implementa ``Engine::CreateApplication()`` retornando ``new Sandbox``

### Diretórios de Inclusão
- Incluídos no alvo da engine:
  - `Engine/src`
  - `Engine/src/Engine`
  - `Engine/vendor/spdlog/include`
  - `Engine/vendor/Engine/Events`

## Checklist de Implementação

- [x] Setup inicial (CMake, submódulos, logging).
- [ ] Renderizar triângulo (janela abre, triângulo visível, sem erro de GL).
- [ ] Renderizar quad.
- [ ] Renderizar cubo.
- [ ] Aplicar rotação a 60 FPS constantes.
- [ ] Renderizar múltiplos objetos.
- [ ] Adicionar debugging.
- [ ] Implementar iluminação.
- [ ] Renderizar texto.
- [ ] Renderizar partículas.
- [ ] Otimizar com renderização em batch sem flicker.

## Trilha de Aprendizado

- GitHub Project Board.
- Convenção de nomenclatura de branches.
- CMake + testes unitários (GoogleTest).
- Logging centralizado.
- Diretrizes de código C++17/20.
- Outros tópicos relevantes à criação de game engines (matemática para gráficos, sistemas de entrada, ECS, asset pipeline, profiling).
