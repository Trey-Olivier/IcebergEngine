//
// Created by treyo on 8/15/2026.
//
#pragma once

namespace engine {

    enum class AppResult { Continue, Success, Failure };

    enum class EventType { Quit, KeyDown, KeyUp, WindowResized };

    struct Event {
        EventType type;
        int key = 0;       // valid for KeyDown/KeyUp
        int width = 0;      // valid for WindowResized
        int height = 0;
    };

    class Application {
    public:
        bool IsRunning() const { return m_Running; }
        void RequestQuit() { m_Running = false; }

        virtual ~Application() = default;
        virtual AppResult Init(int argc, char** argv) = 0;
        virtual AppResult Update() = 0;
        virtual AppResult OnEvent(const Event& e) = 0;
        virtual void Shutdown(AppResult result) = 0;

    protected:
        bool m_Running = true;
    };

    // Game implements this factory; engine calls it.
    Application* CreateApplication();

} // namespace engine
