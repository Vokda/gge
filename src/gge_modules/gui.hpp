#pragma once
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_sdl2.h"
#include "../imgui/imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

#include "../logger.hpp"
#include "gge_module.hpp"

/*
 * this class uses the Dear Imgui library to handle gui.
 * The only modifications on the library are to integrate it to GGE.
 */

namespace gge
{
    class GUI: public GGE_module
    {
        public:
            GUI(SDL_Window* window);
            ~GUI();

            // Poll and handle events (inputs, window resize, etc.)
            // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
            // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
            // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
            // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
            bool want_capture_mouse() { return (bool)_io.WantCaptureMouse;}
            bool want_capture_keyboard() {return (bool)_io.WantCaptureKeyboard;}

        private:
            Logger::Log& _log;

            // imgui stuff
            ImGuiIO _io;
            SDL_GLContext _gl_context;
    };
}
