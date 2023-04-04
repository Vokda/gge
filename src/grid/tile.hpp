#pragma once
#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <memory>
#include <list>
using namespace std;

class Agent;

class Tile: public enable_shared_from_this<Tile>
{
	public:
		Tile(SDL_Point center_point, int size, SDL_Color c);
		virtual ~Tile() = default;

		map<string,void*>::mapped_type& operator[](const string& name) { return _tile_data[name]; }

		const SDL_Point& get_position() const { return _position; }

		const SDL_Color& get_color() const {return _color;}
		void set_color(const SDL_Color c) {_color = c;}

		const std::vector<SDL_Point>& get_corners() const { return _corners; }
		std::vector<SDL_Point>& get_corners() { return _corners; }

		// get coordinate string (mainly for <<-op)
		virtual string coord_to_string() const = 0;

		void place_agent(shared_ptr<Agent>);
		shared_ptr<Agent> remove_agent(shared_ptr<Agent>);
		bool move_agent(shared_ptr<Agent> agent, shared_ptr<Tile> dest);
		list<shared_ptr<Agent>> get_agents() const { return _tile_agents; }

	protected:
		virtual void calculate_corners(SDL_Point& c, int s) = 0;
		virtual SDL_Point calculate_corner(SDL_Point& center, int, int ) = 0;

		SDL_Point _position; // center point position x y
		std::vector<SDL_Point> _corners;

		SDL_Color _color;
		bool blink = false;
		map<string, void*> _tile_data;
		list<shared_ptr<Agent>> _tile_agents; // agents on the tile

};

std::ostream& operator<<(std::ostream& ost, const Tile&);
