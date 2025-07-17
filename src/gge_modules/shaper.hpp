#pragma once
#include "gge_module.hpp"
class Graphics;
using namespace std;
#include "componenter.hpp"
#include "../logger.hpp"

struct Shape: public Base_component
{
    SDL_Point position; // middle position
    SDL_Rect size;
    // TODO what to draw?
};

class Shaper: public Componenter, public GGE_module
{
    public:
        enum Shape_type {RECTANGLE};
        Shaper(/*shared_ptr<Graphics> g*/);
        ~Shaper() = default;

        size_t create_shape(int shape_type, const SDL_Rect&, int ms); 

        size_t create_rectangle(const SDL_Rect& size, int ms);

    private:
        //shared_ptr<Graphics> _graphics;
        log4cpp::Category& _log;
        Logger::Log_stream _log_stream;
};
