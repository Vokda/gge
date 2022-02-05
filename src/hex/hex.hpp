#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <iostream>
#include "cube_coordinate.hpp"
#include <memory>
#include "../chai_object.hpp"

class Hex
{
	public:
		// for hex calculations
		Hex(int q_, int r_, int s_, int size);

		// to actually create a new hex (no custom data)
		Hex(int row, int col, int size, SDL_Point offset);
		/*Hex(
				int row, 
				int col, 
				int size,
				SDL_Point offset
				);*/

		//Hex& operator=(const Hex& h);

		//SDL_Point hex_to_pixel(const Hex& hex);

		Cube_coordinate axial_to_cube (const Hex& h) const;
		Cube_coordinate axial_to_cube (int q, int r) const;
		SDL_Point cube_to_axial (const Cube_coordinate&) const;

		SDL_Point hex_to_pixel(const Hex& h, int size);

		const SDL_Point& get_position() const { return _position; }

		//std::vector<int>& get_corners() { return _corners; }
		const std::vector<SDL_Point>& get_corners() const { return _corners; }
		const Cube_coordinate& get_cube_coordinate() const { return _cube_coordinate; }


	private:
		// cube coordinates
		Cube_coordinate _cube_coordinate;

		// position x y
		SDL_Point _position;

		std::vector<SDL_Point> _corners;

		void calculate_corners(SDL_Point& c, int s);
		SDL_Point calculate_corner(SDL_Point& center, int, int );

		std::shared_ptr<Chai_object> _in_hex_data = nullptr;
		std::shared_ptr<Chai_object> _on_hex_data = nullptr;

};

std::ostream& operator<<(std::ostream& ost, const Hex&);
