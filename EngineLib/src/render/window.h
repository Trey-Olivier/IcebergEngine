//
// Created by treyo on 8/15/2026.
//

#pragma once

#include <SDL3/SDL.h>

class window {

    public:
    window();
    ~window();

    private:
    SDL_Window* sdl_window = nullptr;
    SDL_GLContext gl_context;

};

