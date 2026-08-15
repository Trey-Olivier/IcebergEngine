//
// Created by treyo on 8/14/2026.
//
#include "include/application.h"

class MyGame : public engine::Application {
public:
    engine::AppResult Init(int argc, char** argv) override {
        // set up game state
        return engine::AppResult::Continue;
    }

    engine::AppResult Update() override {
        // game logic + tell Renderer to draw
        return engine::AppResult::Continue;
    }

    engine::AppResult OnEvent(const engine::Event& e) override {
        if (e.type == engine::EventType::Quit)
            return engine::AppResult::Success;
        return engine::AppResult::Continue;
    }

    void Shutdown(engine::AppResult result) override {}
};

engine::Application* engine::CreateApplication() {
    return new MyGame();
}