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
            // Window close requests (user clicked the X) and quit events
            // should be treated the same: request engine shutdown.
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            case SDL_EVENT_QUIT:
                ev.type = engine::EventType::Quit;
                break;
            case SDL_EVENT_KEY_DOWN:
                ev.type = engine::EventType::KeyDown;
                ev.key = static_cast<int>(e.key.key);
                break;
            case SDL_EVENT_KEY_UP:
                ev.type = engine::EventType::KeyUp;
                ev.key = static_cast<int>(e.key.key);
                break;
            case SDL_EVENT_WINDOW_RESIZED:
                ev.type = engine::EventType::WindowResized;
                ev.width = e.window.data1;
                ev.height = e.window.data2;
                break;
            default:
                // Return a dummy/none type instead of forcing a Quit
                ev.type = static_cast<engine::EventType>(-1);
                break;
        }
        return ev;
    }

} // namespace

extern "C" SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    SDL_Log("SDL_AppInit: initializing application");
    auto* app = engine::CreateApplication();
    *appstate = app;
    auto r = app->Init(argc, argv);
    SDL_Log("SDL_AppInit: Init returned %d", static_cast<int>(r));
    return ToSDL(r);
}

extern "C" SDL_AppResult SDL_AppIterate(void* appstate) {
    SDL_Log("SDL_AppIterate: calling Update");
    auto r = static_cast<engine::Application*>(appstate)->Update();
    SDL_Log("SDL_AppIterate: Update returned %d", static_cast<int>(r));
    return ToSDL(r);
}

extern "C" SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    SDL_Log("SDL_AppEvent: raw event type=%u", event->type);
    auto ev = ToEngine(*event);
    SDL_Log("SDL_AppEvent: mapped to engine event type=%d", static_cast<int>(ev.type));
    auto r = static_cast<engine::Application*>(appstate)->OnEvent(ev);
    SDL_Log("SDL_AppEvent: OnEvent returned %d", static_cast<int>(r));
    return ToSDL(r);
}

extern "C" void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    auto* app = static_cast<engine::Application*>(appstate);
    app->Shutdown(result == SDL_APP_SUCCESS ? engine::AppResult::Success : engine::AppResult::Failure);
    // Ensure application state is destroyed so any owned resources are released.
    delete app;

    // Ensure SDL cleans up window/context and subsystems. Some platforms may
    // not automatically call SDL_Quit when using the SDL_App* callback API,
    // or there may be library-owned resources that need explicit shutdown.
    SDL_Log("SDL_AppQuit: calling SDL_Quit() to force cleanup");
    SDL_Quit();
}