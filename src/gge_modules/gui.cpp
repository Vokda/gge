#include <sstream>
#include "gui.hpp"
#include "../imgui/imgui_impl_sdl2.h"
#include <SDL.h>
#include "events.hpp"
#include "../imgui/imgui_impl_sdlrenderer2.h"
#include "../script_handling/gge_api.hpp"

using namespace gge;

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

GUI::GUI(SDL_Window* window, SDL_Renderer* renderer, GGE_API& ga):
    GGE_module(rgm::GUI),
    _renderer(renderer),
    _gge_api(ga)
{
    // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //_io = io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);


    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    // - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);

    _log.info("GUI Initialized");
}

bool GUI::want_capture_mouse()
{
    ImGuiIO& io = ImGui::GetIO();
    return io.WantCaptureMouse;
}

bool GUI::want_capture_keyboard()
{
    ImGuiIO& io = ImGui::GetIO();
    return io.WantCaptureKeyboard;
}

void GUI::handle_focus(ImGuiIO& io)
{
    // make focus work like in i3
    // i.e. hover = focus
    if(ImGui::IsWindowHovered() and !ImGui::IsWindowFocused())
    {
        io.WantCaptureMouse = 1;
        io.WantCaptureKeyboard = 1;
    }
    else if(!ImGui::IsWindowHovered() and ImGui::IsWindowFocused())
    {
        io.WantCaptureMouse = 0;
        io.WantCaptureKeyboard = 0;
    }
}

void GUI::draw()
{
    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGuiIO& io = ImGui::GetIO();
    //demo(); // activate to show demo windows


    // main menu
    ImGui::BeginMainMenuBar();
    handle_focus(io);
    element_handling();
    ImGui::EndMainMenuBar();

    // Rendering
    ImGui::Render();
    SDL_RenderSetScale(_renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    /*SDL_SetRenderDrawColor(_renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
    SDL_RenderClear(_renderer);*/
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), _renderer);
    SDL_RenderPresent(_renderer);
}

bool GUI::process_event(SDL_Event& event)
{ 
    _log.debug("event processed");
    ImGui_ImplSDL2_ProcessEvent(&event);
    return (want_capture_mouse() or want_capture_keyboard());
}

void GUI::create_button(const string& s, void* fn)
{
    gui_element ge = {s, BUTTON, fn};
    _gui_elements.push_back(ge);
}

GUI::~GUI()
{
    // Cleanup
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void GUI::element_handling()
{
    for(gui_element ge : _gui_elements)
    {
        switch(ge.get)
        {
            case(BUTTON):
                if(ImGui::Button(ge.label.c_str()))
                {
                    _log.info( "click");
                    _gge_api.call_script_fn(ge.fn);
                }
                break;
            default:
                throw runtime_error("cannot create gui element");
                break;
        }
    }
}

void GUI::demo()
{
    // TODO (tmp) Our state 
    bool show_demo_window = true;
    bool show_another_window = true;

    ImGuiIO& io = ImGui::GetIO();

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Text("want capture mouse %i", (int)io.WantCaptureMouse);
        ImGui::Text("want capture mouse %f, %f ", io.MousePos.x, io.MousePos.y);
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }
}
