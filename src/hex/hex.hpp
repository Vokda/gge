#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <iostream>
#include "coords.hpp"
#include <map>
using namespace std;

class Hex
{
	public:
		Hex(
				int col, 
				int row, 
				cube_coord, 
				SDL_Point,
				int size,
				SDL_Color c = {255, 255, 255, 255}
		   );

		//~Hex();

		// old implementation
		//Hex(int row, int col, int size, SDL_Point offset, const Utils& u);

		//Hex& operator=(const Hex& h);

		const SDL_Point& get_position() const { return _position; }

		const std::vector<SDL_Point>& get_corners() const { return _corners; }
		std::vector<SDL_Point>& get_corners() { return _corners; }

		const cube_coord& get_cube_coordinate() const { return _cube_coordinate; }

		const SDL_Color& get_color() const {return _hex_color;}

		cube_coord get_cube_coords() { return _cube_coordinate; }

		void set_color(const SDL_Color c) {_hex_color = c;}

		// custom hex data
		//void set_custom_data(const string&, void* data, size_t size);
		//void* get_custom_data(const string&);
		map<string,void*>::mapped_type& operator[](const string& name) { return _hex_data[name]; }

	private:
		cube_coord _cube_coordinate; // cube coordinates
		SDL_Point _position; // center point position x y

		std::vector<SDL_Point> _corners;

		void calculate_corners(SDL_Point& c, int s);
		SDL_Point calculate_corner(SDL_Point& center, int, int );

		// hex properties
		SDL_Color _hex_color;
		bool blink = false;
		map<string, void*> _hex_data;
};

std::ostream& operator<<(std::ostream& ost, const Hex&);
