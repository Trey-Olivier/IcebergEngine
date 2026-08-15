//
// Created by treyo on 8/15/2026.
//
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#include "include/application.h"

namespace {

    SDL_AppResult ToSDL(engine::AppResult r) {
        switch (r) {
            case engine::AppResult::Continue: return SDL_APP_CONTINUE;
            case engine::AppResult::Success:  return SDL_APP_SUCCESS;
            default:                          return SDL_APP_FAILURE;
        }
    }

    engine::Event ToEngine(const SDL_Event& e) {
        engine::Event ev{};
        switch (e.type) {
            case SDL_EVENT_QUIT:
                ev.type = engine::EventType::Quit;
                break;
            case SDL_EVENT_KEY_DOWN:
                ev.type = engine::EventType::KeyDown;
                ev.key = e.key.key;
                break;
            case SDL_EVENT_KEY_UP:
                ev.type = engine::EventType::KeyUp;
                ev.key = e.key.key;
                break;
            case SDL_EVENT_WINDOW_RESIZED:
                ev.type = engine::EventType::WindowResized;
                ev.width = e.window.data1;
                ev.height = e.window.data2;
                break;
            default:
                ev.type = engine::EventType::Quit; // fallback; refine as needed
                break;
        }
        return ev;
    }

} // namespace

extern "C" SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    auto* app = engine::CreateApplication();
    *appstate = app;
    return ToSDL(app->Init(argc, argv));
}

extern "C" SDL_AppResult SDL_AppIterate(void* appstate) {
    return ToSDL(static_cast<engine::Application*>(appstate)->Update());
}

extern "C" SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    auto ev = ToEngine(*event);
    return ToSDL(static_cast<engine::Application*>(appstate)->OnEvent(ev));
}

extern "C" void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    auto* app = static_cast<engine::Application*>(appstate);
    app->Shutdown(result == SDL_APP_SUCCESS ? engine::AppResult::Success : engine::AppResult::Failure);
    delete app;
}