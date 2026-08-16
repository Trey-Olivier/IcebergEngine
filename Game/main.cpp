//
// Created by treyo on 8/14/2026.
//
#include "include/application.h"
#include "SDL3/SDL_log.h"

class MyGame : public engine::Application {
public:
    engine::AppResult Init(int argc, char** argv) override {
        m_Running = true;
        return engine::AppResult::Continue;
    }

    engine::AppResult Update() override {
        // If quit was requested, return Success to tell SDL to shut down
        if (!m_Running)
            return engine::AppResult::Success;

        // game logic + tell Renderer to draw
        return engine::AppResult::Continue;
    }

    engine::AppResult OnEvent(const engine::Event& e) override {
        if (e.type == engine::EventType::Quit) {
            SDL_Log("Quit event received");
            RequestQuit();
            return engine::AppResult::Success;
        }
        return engine::AppResult::Continue;
    }

    void Shutdown(engine::AppResult result) override {}
};

engine::Application* engine::CreateApplication() {
    return new MyGame();
}