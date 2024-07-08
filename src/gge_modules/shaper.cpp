#include "shaper.hpp"
#include "graphics.hpp"

Shaper::Shaper(/*shared_ptr<Graphics> g*/):
    GGE_module(SHAPER),
    _log(Logger::get_instance().add_category("Shaper")),
    _log_stream(
            Logger::get_instance().get_category_stream("Shaper", log4cpp::Priority::DEBUG)
            )
{
}

size_t Shaper::create_shape(int shape_type, const SDL_Rect& sdlr, int ms)
{
    _log.debug("Creating a shape");
    switch((Shape_type)shape_type)
    {
        case(RECTANGLE): 
            return create_rectangle(sdlr, ms);
            break;
        default:
            _log.error("Shape to be created not recognized");
            return -1;
    }
}
                
size_t Shaper::create_rectangle(const SDL_Rect& rectangle, int ms)
{
    Shape shape;
    shape.size = rectangle;
    shape.position.x = rectangle.x;
    shape.position.y = rectangle.y;

    _log_stream << "Creating rectangle" ;
    _log_stream << "size " << shape.size << " @ " << shape.position ;

	_components.push_back(make_shared<Shape>(shape));
	return _components.size() -1;
}
