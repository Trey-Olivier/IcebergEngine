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
        virtual ~Application() = default;
        virtual AppResult Init(int argc, char** argv) = 0;
        virtual AppResult Update() = 0;
        virtual AppResult OnEvent(const Event& e) = 0;
        virtual void Shutdown(AppResult result) = 0;
    };

    // Game implements this factory; engine calls it.
    Application* CreateApplication();

} // namespace engine
