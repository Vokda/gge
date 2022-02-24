#pragma once

#include <vector>
#include <unordered_map>

//class Hex;
#include "hex.hpp"
#include "orientation.hpp"
#include "utils.hpp"


using namespace std;

class Hex_grid
{
	public:

		Hex_grid(size_t w, size_t h, double hex_size, Hex_orientation ho, Coordinate_system cs);

		//Hex hex_add(const Hex& a, const Hex& b);

		// getters
		std::vector<Hex>& get_grid() { return _grid; };
		const std::vector<Hex>& get_grid() const { return _grid; }

		Hex& get_hex(int q, int  r, int s);
		Hex& get_hex(size_t i) { return _grid[i]; };
		int get_hex_index(cube_coord c);
		
		/* ugly special case for the gge api 
		 * so you can do something like
		 * grid = core.get_grid()
		 * grid->_utils.<grid_related stuff>();
		 */
		Utils _utils;

	private:
		// used to map qrs coords to index in vector
		typedef std::unordered_map<int, int> cube_coords_map;
		cube_coords_map _cube_coords_to_i_map;

		void map_cube_to_i(cube_coord, size_t i);
		int hash_cube_coord(int q, int r, int s);

		// vars
		std::vector<Hex> _grid;
		int _hex_size;
		Layout _layout;

		/*
		   Hex hex_subtract(Hex a, Hex b)
		   {
		   return Hex(a.q - b.q, a.r - b.r, a.s - b.s);
		   }


		   Hex hex_scale(Hex a, int k)
		   {
		   return Hex(a.q * k, a.r * k, a.s * k);
		   }


		   Hex hex_rotate_left(Hex a)
		   {
		   return Hex(-a.s, -a.q, -a.r);
		   }


		   Hex hex_rotate_right(Hex a)
		   {
		   return Hex(-a.r, -a.s, -a.q);
		   }


		   const vector<Hex> hex_directions = {Hex(1, 0, -1), Hex(1, -1, 0), Hex(0, -1, 1), Hex(-1, 0, 1), Hex(-1, 1, 0), Hex(0, 1, -1)};
		   Hex hex_direction(int direction)
		   {
		   return hex_directions[direction];
		   }


		   Hex hex_neighbor(Hex hex, int direction)
		   {
		   return hex_add(hex, hex_direction(direction));
		   }


		   const vector<Hex> hex_diagonals = {Hex(2, -1, -1), Hex(1, -2, 1), Hex(-1, -1, 2), Hex(-2, 1, 1), Hex(-1, 2, -1), Hex(1, 1, -2)};
		   Hex hex_diagonal_neighbor(Hex hex, int direction)
		   {
		   return hex_add(hex, hex_diagonals[direction]);
		   }


		   int hex_length(Hex hex)
		   {
		   return int((abs(hex.q) + abs(hex.r) + abs(hex.s)) / 2);
		   }


		   int hex_distance(Hex a, Hex b)
		   {
		   return hex_length(hex_subtract(a, b));
		   }



		   Hex hex_round(FractionalHex h)
		   {
		   int qi = int(round(h.q));
		   int ri = int(round(h.r));
		   int si = int(round(h.s));
		   double q_diff = abs(qi - h.q);
		   double r_diff = abs(ri - h.r);
		   double s_diff = abs(si - h.s);
		   if (q_diff > r_diff && q_diff > s_diff)
		   {
		   qi = -ri - si;
		   }
		   else	if (r_diff > s_diff)
		{
			ri = -qi - si;
		}
		   else
		   {
			   si = -qi - ri;
		   }
		   return Hex(qi, ri, si);
}


FractionalHex hex_lerp(FractionalHex a, FractionalHex b, double t)
{
	return FractionalHex(a.q * (1.0 - t) + b.q * t, a.r * (1.0 - t) + b.r * t, a.s * (1.0 - t) + b.s * t);
}


vector<Hex> hex_linedraw(Hex a, Hex b)
{
	int N = hex_distance(a, b);
	FractionalHex a_nudge = FractionalHex(a.q + 1e-06, a.r + 1e-06, a.s - 2e-06);
	FractionalHex b_nudge = FractionalHex(b.q + 1e-06, b.r + 1e-06, b.s - 2e-06);
	vector<Hex> results = {};
	double step = 1.0 / max(N, 1);
	for (int i = 0; i <= N; i++)
	{
		results.push_back(hex_round(hex_lerp(a_nudge, b_nudge, step * i)));
	}
	return results;
}



const int EVEN = 1;
const int ODD = -1;
OffsetCoord qoffset_from_cube(int offset, Hex h)
{
	int col = h.q;
	int row = h.r + int((h.q + offset * (h.q & 1)) / 2);
	if (offset != EVEN && offset != ODD)
	{
		throw "offset must be EVEN (+1) or ODD (-1)";
	}
	return OffsetCoord(col, row);
}


Hex qoffset_to_cube(int offset, OffsetCoord h)
{
	int q = h.col;
	int r = h.row - int((h.col + offset * (h.col & 1)) / 2);
	int s = -q - r;
	if (offset != EVEN && offset != ODD)
	{
		throw "offset must be EVEN (+1) or ODD (-1)";
	}
	return Hex(q, r, s);
}


OffsetCoord roffset_from_cube(int offset, Hex h)
{
	int col = h.q + int((h.r + offset * (h.r & 1)) / 2);
	int row = h.r;
	if (offset != EVEN && offset != ODD)
	{
		throw "offset must be EVEN (+1) or ODD (-1)";
	}
	return OffsetCoord(col, row);
}


Hex roffset_to_cube(int offset, OffsetCoord h)
{
	int q = h.col - int((h.row + offset * (h.row & 1)) / 2);
	int r = h.row;
	int s = -q - r;
	if (offset != EVEN && offset != ODD)
	{
		throw "offset must be EVEN (+1) or ODD (-1)";
	}
	return Hex(q, r, s);
}



DoubledCoord qdoubled_from_cube(Hex h)
{
	int col = h.q;
	int row = 2 * h.r + h.q;
	return DoubledCoord(col, row);
}


Hex qdoubled_to_cube(DoubledCoord h)
{
	int q = h.col;
	int r = int((h.row - h.col) / 2);
	int s = -q - r;
	return Hex(q, r, s);
}


DoubledCoord rdoubled_from_cube(Hex h)
{
	int col = 2 * h.q + h.r;
	int row = h.r;
	return DoubledCoord(col, row);
}


Hex rdoubled_to_cube(DoubledCoord h)
{
	int q = int((h.col - h.row) / 2);
	int r = h.row;
	int s = -q - r;
	return Hex(q, r, s);
}




const Orientation layout_pointy = Orientation(sqrt(3.0), sqrt(3.0) / 2.0, 0.0, 3.0 / 2.0, sqrt(3.0) / 3.0, -1.0 / 3.0, 0.0, 2.0 / 3.0, 0.5);
const Orientation layout_flat = Orientation(3.0 / 2.0, 0.0, sqrt(3.0) / 2.0, sqrt(3.0), 2.0 / 3.0, 0.0, -1.0 / 3.0, sqrt(3.0) / 3.0, 0.0);
Point hex_to_pixel(Layout layout, Hex h)
{
	Orientation M = layout.orientation;
	Point size = layout.size;
	Point origin = layout.origin;
	double x = (M.f0 * h.q + M.f1 * h.r) * size.x;
	double y = (M.f2 * h.q + M.f3 * h.r) * size.y;
	return Point(x + origin.x, y + origin.y);
}


FractionalHex pixel_to_hex(Layout layout, Point p)
{
	Orientation M = layout.orientation;
	Point size = layout.size;
	Point origin = layout.origin;
	Point pt = Point((p.x - origin.x) / size.x, (p.y - origin.y) / size.y);
	double q = M.b0 * pt.x + M.b1 * pt.y;
	double r = M.b2 * pt.x + M.b3 * pt.y;
	return FractionalHex(q, r, -q - r);
}


Point hex_corner_offset(Layout layout, int corner)
{
	Orientation M = layout.orientation;
	Point size = layout.size;
	double angle = 2.0 * M_PI * (M.start_angle - corner) / 6.0;
	return Point(size.x * cos(angle), size.y * sin(angle));
}


vector<Point> polygon_corners(Layout layout, Hex h)
{
	vector<Point> corners = {};
	Point center = hex_to_pixel(layout, h);
	for (int i = 0; i < 6; i++)
	{
		Point offset = hex_corner_offset(layout, i);
		corners.push_back(Point(center.x + offset.x, center.y + offset.y));
	}
	return corners;
}
*/
};
