#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <iostream>
#include "coords.hpp"
#include <memory>
#include "../chai_object.hpp"

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

		// old implementation
		//Hex(int row, int col, int size, SDL_Point offset, const Utils& u);

		//Hex& operator=(const Hex& h);

		const SDL_Point& get_position() const { return _position; }

		//std::vector<int>& get_corners() { return _corners; }
		const std::vector<SDL_Point>& get_corners() const { return _corners; }
		const cube_coord& get_cube_coordinate() const { return _cube_coordinate; }

		const SDL_Color& get_color() const {return _hex_color;}

		cube_coord get_cube_coords() { return _cube_coordinate; }

		void set_color(const SDL_Color c) {_hex_color = c;}

	private:
		cube_coord _cube_coordinate; // cube coordinates
		SDL_Point _position; // center point position x y


		std::vector<SDL_Point> _corners;

		void calculate_corners(SDL_Point& c, int s);
		SDL_Point calculate_corner(SDL_Point& center, int, int );

		// hex properties
		SDL_Color _hex_color;
		bool blink = false;

		std::shared_ptr<Chai_object> _in_hex_data = nullptr;
		std::shared_ptr<Chai_object> _on_hex_data = nullptr;

};

std::ostream& operator<<(std::ostream& ost, const Hex&);
