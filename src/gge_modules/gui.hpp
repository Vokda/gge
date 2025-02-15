#pragma once
#include "../imgui/imgui.h"

#include "gge_module.hpp"
#include <vector>
class SDL_Renderer;
class GGE_API;

/*
 * this class uses the Dear Imgui library to handle gui.
 * The only modifications on the library are to integrate it to GGE.
 */

enum gui_element_type {BUTTON};

namespace gge
{
    class GUI: public GGE_module
    {
        public:
            GUI(SDL_Window* window, SDL_Renderer* renderer, GGE_API& ga);
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

            void demo();

            // creating gui
            void create_button(const string& s, void* fn);


        private:
            void handle_focus(ImGuiIO&);

            struct gui_element
            {
                const string label;
                gui_element_type get;
                void* fn; // can be guile function. Don't call willy nilly!
            };

            // imgui stuff
            //std::optional<std::reference_wrapper<ImGuiIO>> _io_ref;
            SDL_Renderer* _renderer;
            GGE_API& _gge_api;

            std::vector<gui_element> _gui_elements;

            void element_handling();
    };
}
