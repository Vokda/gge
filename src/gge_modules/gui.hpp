#pragma once
#include "../imgui/imgui.h"

#include "../logger.hpp"
#include "gge_module.hpp"
class SDL_Renderer;

/*
 * this class uses the Dear Imgui library to handle gui.
 * The only modifications on the library are to integrate it to GGE.
 */

namespace gge
{
    class GUI: public GGE_module
    {
        public:
            GUI(SDL_Window* window, SDL_Renderer* renderer);
            ~GUI();

            void draw();

            // Poll and handle events (inputs, window resize, etc.)
            // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
            // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
            // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
            // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
            bool want_capture_mouse() { return (bool)_io.WantCaptureMouse;}
            bool want_capture_keyboard() {return (bool)_io.WantCaptureKeyboard;}
            void process_event(SDL_Event& event); 

        private:
            Logger::Log& _log;

            // imgui stuff
            ImGuiIO _io;
            SDL_GLContext _gl_context;
            SDL_Renderer* _renderer;
    };
}
