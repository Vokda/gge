#pragma once
#include "../imgui/imgui.h"

#include "../logger.hpp"
#include "gge_module.hpp"
/*#include <optional>
#include <functional>*/
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
            bool want_capture_mouse(); 
            bool want_capture_keyboard();
            //void process_event(SDL_Event& event); 
            bool process_event(SDL_Event& event);

        private:
            Logger::Log& _log;
            Logger::Log& _debug_log;

            // imgui stuff
            //std::optional<std::reference_wrapper<ImGuiIO>> _io_ref;
            SDL_Renderer* _renderer;
    };
}
